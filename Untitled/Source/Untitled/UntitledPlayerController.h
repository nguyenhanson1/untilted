// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UntitledPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNTITLED_API AUntitledPlayerController : public APlayerController
{
	GENERATED_BODY()

	FTimerHandle TimerHandle_Respawn;
public:
	/** Condition and function for the Pause Menu*/
	bool bPauseMenuVisible;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HUD")
	void DisplayPauseMenu();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HUD")
	void RemovePauseMenu();
	
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void TogglePauseMenu();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> WPauseMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UPauseMenu* PauseMenu;

	void OnKilled();

	void Respawn();

protected:
	virtual void BeginPlay() override;


};
