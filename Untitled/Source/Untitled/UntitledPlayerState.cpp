// Fill out your copyright notice in the Description page of Project Settings.


#include "UntitledPlayerState.h"
#include "Net/UnrealNetwork.h"



void AUntitledPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUntitledPlayerState, bTeamB);

}