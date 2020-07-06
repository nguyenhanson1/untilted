// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget_Base.h"
#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY();

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;

};

/**
 * 
 */
UCLASS()
class UNTITLED_API UMainMenu : public UWidget_Base
{
	GENERATED_BODY()
public:
	UMainMenu(const FObjectInitializer & ObjectInitializer);

	void SetServerList(TArray<FServerData> ServerNames);

	void SelectIndex(uint32 Index);
protected:
	virtual bool Initialize();


private:

	TSubclassOf<class UUserWidget> ServerRowClass;

	UPROPERTY(meta = (BindWidget))
		class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinServerButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
		class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* ServerHostName;

	UPROPERTY(meta = (BindWidget))
		class UButton* ConfirmHostButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* CancelHostButton;


	UPROPERTY(meta = (BindWidget))
		class UPanelWidget* ServerList;




	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void OpenJoinMenu();

	UFUNCTION()
		void OpenHostMenu();

	UFUNCTION()
		void OpenMainMenu();

	UFUNCTION()
		void JoinServer();

	UFUNCTION()
		void QuitPressed();



	TOptional<uint32> SelectedIndex;

	void UpdateChildren();
};
