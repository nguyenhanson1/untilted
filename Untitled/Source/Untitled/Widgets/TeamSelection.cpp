// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamSelection.h"
#include "Components/Button.h"
#include "PlayerStateInterface.h"



bool UTeamSelection::Initialize() {
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(TeamAButton != nullptr)) return false;
	TeamAButton->OnClicked.AddDynamic(this, &UTeamSelection::ChooseTeamA);

	if (!ensure(TeamBButton != nullptr)) return false;
	TeamBButton->OnClicked.AddDynamic(this, &UTeamSelection::ChooseTeamB);


	return true;
}

void UTeamSelection::ChooseTeamA()
{
	
}

void UTeamSelection::ChooseTeamB()
{

}




