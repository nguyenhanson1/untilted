// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "UntitledPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class UNTITLED_API AUntitledPlayerStart : public APlayerStart
{
	GENERATED_BODY()

	

public:
	UPROPERTY(EditAnywhere, Category=  "Defaults")
	bool bTeamB;
};
