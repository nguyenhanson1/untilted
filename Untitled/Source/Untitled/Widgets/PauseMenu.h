// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget_Base.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class UNTITLED_API UPauseMenu : public UWidget_Base
{
	GENERATED_BODY()
public:
	/** Display the pause menu by seting vibility of the widget and create additional features in blueprint*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HUD")
	void DisplayPauseMenu();

	/** Remove the pause menu by seting vibility of the widget and create additional features in blueprint*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HUD")
	void RemovePauseMenu();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void TogglePauseMenu();

	bool bPauseMenuActive;

protected:
	virtual bool Initialize();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
	
	UFUNCTION()
	void ToMainMenu();
};
