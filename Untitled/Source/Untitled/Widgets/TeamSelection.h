// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TeamSelection.generated.h"

/**
 * 
 */
UCLASS()
class UNTITLED_API UTeamSelection : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* TeamAButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* TeamBButton;
	
protected:
	virtual bool Initialize();

	class UPlayerStateInterface* PlayerState;

public:
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ChooseTeamA();
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ChooseTeamB();

};
