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
	/** Constructor for MainMenu with ObjectInitializer to find blurprint with FClassFinder
	*	FObjectInitializer &  ObjectInitializer : Call at the beginning of class contructor for FClassFinder
	*/
	UMainMenu(const FObjectInitializer & ObjectInitializer);

	/** Set the array of FServerData for displaying the server information
	*	TArray<FServerData> ServerNames : array of struct FServerData for server information
	*/
	void SetServerList(TArray<FServerData> ServerNames);

	/** Select the index of server in the ServerList for player to connect
	*	uint32 Index : index of the selected server
	*/
	void SelectIndex(uint32 Index);
protected:

	virtual bool Initialize();


private:

	TSubclassOf<class UUserWidget> ServerRowClass;
	/** Button that transition to Host Menu*/
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	/** Button that transition to Join Menu*/
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	/** Button that exit Join Menu to MainMenu*/
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	/** Button that Join Server and transition to selected server in the ServerList*/
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinServerButton;

	/** Button that Quit the Game*/
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	/** Button that Control the MenuSwither to switch between Main, Host, and Join Menu*/
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	/** Widget for the Join Menu*/
	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	/** Widget for the Main Menu*/
	UPROPERTY(meta = (BindWidget))
		class UWidget* MainMenu;


/* Host Menu*/
	/** Widget for the Host Menu*/
	UPROPERTY(meta = (BindWidget))
		class UWidget* HostMenu;

	/** Editable TextBox to take in the server name when hosting*/
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* ServerHostName;

	/** Button to Host the Server in Host Menu*/
	UPROPERTY(meta = (BindWidget))
		class UButton* ConfirmHostButton;

	/** Button to exit HostMenu to return to MainMenu*/
	UPROPERTY(meta = (BindWidget))
		class UButton* CancelHostButton;

	/** The panel that hold all of the servers with the same steam IP*/
	UPROPERTY(meta = (BindWidget))
		class UPanelWidget* ServerList;



	/** Call to Host the Server when ConfirmHostButton clicked and There is something written inside the ServerHostName*/
	UFUNCTION()
	void HostServer();

	/** Call to Open the Join Menu through changing the index inside the MenuSwitcher*/
	UFUNCTION()
	void OpenJoinMenu();

	/** Call to Open the Host Menu through changing the index inside the MenuSwitcher*/
	UFUNCTION()
	void OpenHostMenu();

	/** Call to Return to the Main Menu through changing the index inside the MenuSwitcher*/
	UFUNCTION()
	void OpenMainMenu();

	/** Call to join a selected server within the ServeList, This only works after the user clicked on a valid index of server*/
	UFUNCTION()
	void JoinServer();

	/** Call to Quit the Game*/
	UFUNCTION()
	void QuitPressed();

	/** Variable that hold the selected index of the ServerList*/
	TOptional<uint32> SelectedIndex;

	/** Update children of the ServerList, part of the RefreshServerList Method*/
	void UpdateChildren();
};
