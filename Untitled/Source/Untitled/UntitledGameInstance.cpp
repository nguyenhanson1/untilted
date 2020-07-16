// Fill out your copyright notice in the Description page of Project Settings.


#include "UntitledGameInstance.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"


#include "Widgets/MainMenu.h"
#include "Widgets/Widget_Base.h"

const static FName SESSION_NAME = TEXT("GameSession");
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("SessionName");

UUntitledGameInstance::UUntitledGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/Widget/W_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	MenuClass = MenuBPClass.Class;

}

void UUntitledGameInstance::LoadMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
	if (!ensure(MenuClass != nullptr)) return;
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
	Menu->SetUp();
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
	Menu->SetMenuInterface(this);
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());

}



void UUntitledGameInstance::LoadMainMenu() {
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(TEXT("/Game/Maps/Menu"), ETravelType::TRAVEL_Absolute);
}

void UUntitledGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		//SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 10000;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		UE_LOG(LogTemp, Warning, TEXT("Starting Find Session!"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());

	}
}

void UUntitledGameInstance::StartSession()
{
	if (SessionInterface.IsValid())
	{
		SessionInterface->StartSession(SESSION_NAME);
	}
}

void UUntitledGameInstance::Init() {
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found System %s"), *Subsystem->GetSubsystemName().ToString());
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid()) {
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UUntitledGameInstance::FOnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UUntitledGameInstance::FOnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UUntitledGameInstance::FOnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UUntitledGameInstance::FOnJoinSessionComplete);

		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found No SubSystem"));
	}
}

void UUntitledGameInstance::Host(FString ServerName)
{
	DesiredServerName = ServerName;
	if (SessionInterface.IsValid()) {
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}

	}
}

void UUntitledGameInstance::FOnCreateSessionComplete(FName SessionName, bool Success) {
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not Create Session"));
		return;
	}
	if (Menu != nullptr)
	{
		Menu->TearDown();
	}
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Maps/FirstPersonExampleMap?listen");



}

void UUntitledGameInstance::FOnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSession();
	}
}

void UUntitledGameInstance::FOnFindSessionsComplete(bool Success)
{

	if (Success && SessionSearch.IsValid() && Menu != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finish Find Session"));
		TArray<FServerData> ServerNames;

		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session names: %s"), *SearchResult.GetSessionIdStr());
			FServerData Data;
			Data.Name = SearchResult.GetSessionIdStr();
			Data.MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
			Data.CurrentPlayers = Data.MaxPlayers - SearchResult.Session.NumOpenPublicConnections;
			Data.HostUsername = SearchResult.Session.OwningUserName;
			FString ServerName;
			if (SearchResult.Session.SessionSettings.Get(SERVER_NAME_SETTINGS_KEY, ServerName))
			{
				Data.Name = ServerName;
			}
			else
			{
				Data.Name = TEXT("Could not find name.");
			}


			ServerNames.Add(Data);
		}

		Menu->SetServerList(ServerNames);

	}
}


void UUntitledGameInstance::FOnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid()) return;

	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect string."));
		return;
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UUntitledGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;

		if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
		{
			SessionSettings.bIsLANMatch = true;
		}
		else
		{
			SessionSettings.bIsLANMatch = false;
		}
		SessionSettings.NumPublicConnections = 4;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.Set(SERVER_NAME_SETTINGS_KEY, FString(DesiredServerName), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UUntitledGameInstance::Join(uint32 Index)
{
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	if (Menu != nullptr)
	{
		Menu->TearDown();
	}

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);


}

