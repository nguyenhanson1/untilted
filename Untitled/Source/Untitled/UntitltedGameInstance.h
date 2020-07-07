// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Widgets/MenuInterface.h"
#include "OnlineSubSystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "UntitltedGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNTITLED_API UUntitltedGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
public:
	/** Contructor with objectInitializer to use constructor helper and find the correct blueprint class*/
	UUntitltedGameInstance(const FObjectInitializer & ObjectInitializer);

	/** LoadMenu method can be call in blueprint to add MainMenu Widget on screen*/
	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	/** LoadPauseMenu method can be call in blueprint to add PauseMenu Widget on screen*/
	UFUNCTION(BlueprintCallable)
	void LoadPauseMenu();

	/** Init call at the beginning to bind delegates to with method in this script*/
	virtual void Init();

	/** Host method call in console to host a server after given a name as argument
	*	FString ServerName : Name of the server the player is hosting
	*/
	UFUNCTION(Exec)
	void Host(FString ServerName);
	/** Join Method call in console to join the server using the server index within in the ServerList
	*	uint32 Index : The index of the ServerRow within ServerList
	*/
	UFUNCTION(Exec)
	void Join(uint32 Index);

	/** Method call the to return to the MainMenu Level that have the MainMenuWidget */
	virtual void LoadMainMenu();

	/** Method to refresh the ServerList and update with the available servers the player can join*/
	void RefreshServerList() override;

	/** Method to start the Steam session*/
	void StartSession();

private:
	/** Widget Blueprint of MainMenu class*/
	TSubclassOf<class UWidget_Base> MenuClass;
	//TSubclassOf<class UWidget_Base> PauseMenuClass;

	/** Object of the MainMenu class */
	class UMainMenu* Menu;

	/** OnlineSessionPointer for managing the online interaction with steam*/
	IOnlineSessionPtr SessionInterface;
	/** Required TShared Point for online SessionSearch for efficiency find servers between players*/
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	/** Once the Delegate for OnCreateSessionComplete called, It will call this method as a subscriber in Init
	*	This method will remove the MainMenu Widget, Change Input mode, and Travel the player to the game level
	*/
	void FOnCreateSessionComplete(FName SessionName, bool Success);
	/** Once the Delegate for OnDestroySessionComplete called, It attempt to reconnect the session with this method
	*	This method will call to create session connetion with steam network again
	*/
	void FOnDestroySessionComplete(FName SessionName, bool Success);
	/** Once the Delegate for OnFindSessionsComplete called, It will call this method as a subscriber in Init
	*	This method will create an array that will contain all the information from search result and update 
	*	the serverlist on main menu
	*/
	void FOnFindSessionsComplete(bool Success);
	/** Once the Delegate for OnJoinSessionComplete called, It will call this method as a subscriber in Init
	*	This method will get the passed in session name and use it to client travel the player to join a server
	*/
	void FOnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	/** String for the name that the user want to have for the server when hosting*/
	FString DesiredServerName;
	
	/** Create the session when the player want to host the server with predefined settings*/
	void CreateSession();

};
