// Copyright Epic Games, Inc. All Rights Reserved.

#include "UntitledGameMode.h"
#include "UntitledHUD.h"
#include "UntitledCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUntitledGameMode::AUntitledGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUntitledHUD::StaticClass();
}
