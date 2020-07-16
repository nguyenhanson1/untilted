// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UntitledGameMode.generated.h"


UCLASS(minimalapi)
class AUntitledGameMode : public AGameModeBase
{
	GENERATED_BODY()

	

public:
	AUntitledGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	AActor* ChoosePlayerStart(AController* Player);



};



