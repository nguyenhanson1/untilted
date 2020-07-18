// Copyright Epic Games, Inc. All Rights Reserved.

#include "UntitledGameMode.h"
#include "UntitledHUD.h"
#include "UntitledCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UntitledPlayerController.h"
#include "UntitledPlayerState.h"
#include "UntitledPlayerStart.h"
#include "GameFramework/GameStateBase.h"
#include "EngineUtils.h"


AUntitledGameMode::AUntitledGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUntitledHUD::StaticClass();

	PlayerStateClass = AUntitledPlayerState::StaticClass();

}

void AUntitledGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		AUntitledPlayerState* State = Cast<AUntitledPlayerState>(NewPlayer->PlayerState);
		uint8 NumTeamA = 0;
		uint8 NumTeamB = 0;
		if (State && GameState)
		{
			for (APlayerState* It : GameState->PlayerArray)
			{
				AUntitledPlayerState* OtherState = Cast<AUntitledPlayerState>(It);
				if (OtherState->bTeamB)
				{
					NumTeamB++;
				}
				else
				{
					NumTeamA++;
				}
			}
		}

		if (NumTeamA > NumTeamB)
		{
			State->bTeamB = true;
		}
		
	}

}
//
//AActor * AUntitledGameMode::ChoosePlayerStart(AController * Player)
//{
//	if (Player)
//	{
//		AUntitledPlayerState* State = Cast<AUntitledPlayerState>(Player->PlayerState);
//		if (State)
//		{
//			TArray<AUntitledPlayerStart*> Starts;
//			for (TActorIterator<AUntitledPlayerStart> StartItr(GetWorld()); StartItr; ++StartItr)
//			{
//				if (StartItr->bTeamB == State->bTeamB)
//				{
//					Starts.Add(*StartItr);
//				}
//			}
//			return Starts[FMath::RandRange(0, Starts.Num() - 1)];
//		}
//	}
//	return NULL;
//}
