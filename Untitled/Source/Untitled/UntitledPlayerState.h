// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "UntitledPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UNTITLED_API AUntitledPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated,BlueprintReadWrite,VisibleAnywhere)
	bool bTeamB;
};
