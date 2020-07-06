// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNTITLED_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/** Abstract method to Host the Server after taking in a string for the Server Name
	* FString ServerName : Name of the Server the client trying to join
	*/
	virtual void Host(FString ServerName) = 0;

	/** Abstract method to take in an index of server in the menu list that the User is trying to join
	* uint32 Index : The index of server on the menu List
	*/
	virtual void Join(uint32 Index) = 0;

	/** Abstract method to Load the MainMenu of the server*/
	virtual void LoadMainMenu() = 0;

	/** AbStract Method to refresh the server list to check for new servers*/
	virtual void RefreshServerList() = 0;
};
