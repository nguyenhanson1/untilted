// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerStateInterface.generated.h"

UENUM()
enum ETeamState
{
	TS_TeamA UMETA(DisplayName = "TeamA"),
	TS_TeamB UMETA(DisplayName = "TeamB"),
	TS_MAX UMETA(DisplayName = "MAX")
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNTITLED_API IPlayerStateInterface
{
	GENERATED_BODY()

public:
	virtual void ChoosePlayerTeam(ETeamState TeamState) = 0;
};
