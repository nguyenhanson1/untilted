// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"

void UPauseMenu::DisplayPauseMenu_Implementation()
{
	bPauseMenuActive = true;
	SetVisibility(ESlateVisibility::Visible);
}

void UPauseMenu::RemovePauseMenu_Implementation()
{
	bPauseMenuActive = false;
	SetVisibility(ESlateVisibility::Hidden);
}



bool UPauseMenu::Initialize() {
	bool Success = Super::Initialize();
	if (!Success) return false;
	
	bPauseMenuActive = false;

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UPauseMenu::RemovePauseMenu);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::ToMainMenu);

	return true;
}



void UPauseMenu::ToMainMenu()
{
	if (MenuInterface != nullptr) {
		TearDown();
		MenuInterface->LoadMainMenu();
	}

}


void UPauseMenu::TogglePauseMenu()
{
	if (bPauseMenuActive)
	{
		RemovePauseMenu();
	}
	else
	{
		DisplayPauseMenu();
	}
}