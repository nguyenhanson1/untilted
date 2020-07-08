// Fill out your copyright notice in the Description page of Project Settings.


#include "UntitledPlayerController.h"
#include "Widgets/PauseMenu.h"

void AUntitledPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (WPauseMenu)
	{
		PauseMenu = CreateWidget<UPauseMenu>(this, WPauseMenu);
		if (PauseMenu)
		{
			PauseMenu->AddToViewport();
			PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}

}

void  AUntitledPlayerController::DisplayPauseMenu_Implementation()
{
	if (PauseMenu)
	{
		bPauseMenuVisible = true;
		PauseMenu->SetVisibility(ESlateVisibility::Visible);

		FInputModeGameAndUI InputModeGameAndUI;

		SetInputMode(InputModeGameAndUI);
		bShowMouseCursor = true;

	}
}

void AUntitledPlayerController::RemovePauseMenu_Implementation()
{
	if (PauseMenu)
	{
		bPauseMenuVisible = false;

		PauseMenu->SetVisibility(ESlateVisibility::Hidden);

		FInputModeGameOnly InputModeGameOnly;

		SetInputMode(InputModeGameOnly);

		bShowMouseCursor = false;

		
		
	}
}

void AUntitledPlayerController::TogglePauseMenu()
{
	if (bPauseMenuVisible)
	{
		RemovePauseMenu_Implementation();
	}
	else
	{
		DisplayPauseMenu_Implementation();
	}
}