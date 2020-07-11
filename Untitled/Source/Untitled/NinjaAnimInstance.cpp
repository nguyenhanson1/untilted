// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaAnimInstance.h"
#include "UntitledCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"



void UNinjaAnimInstance::NativeInitializeAnimation()
{
	if (!Pawn)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			Ninja = Cast<AUntitledCharacter>(Pawn);
		}
	}
}

void UNinjaAnimInstance::UpdateAnimProperties()
{
	if (!Pawn)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0);
		FRotator CharacterRotator = Pawn->GetActorRotation();
		MovementSpeed = LateralSpeed.Size();
		
		MovementDirection = CalculateDirection(Speed, CharacterRotator);
		bIsInAir = Pawn->GetMovementComponent()->IsFalling();

		if (Ninja == nullptr)
		{
			Ninja = Cast<AUntitledCharacter>(Pawn);
		}
	}
}

//void UNinjaAnimInstance::PlayFootstepSound_Implementation()
//{
//	UWorld* World = GetWorld();
//	if (World)
//	{
//		FHitResult Hit;
//
//		World->LineTraceSingleByChannel(Hit, Ninja->GetActorLocation(), Ninja->GetActorLocation() - FVector(0,0,100.f),ECollisionChannel::ECC_Visibility);
//		
//		EPhysicalSurface SurfaceType = UGameplayStatics::GetSurfaceType(Hit);
//		
//		switch (SurfaceType)
//		{
//		case SurfaceType1: //Wood
//			UGameplayStatics::PlaySoundAtLocation(GetWorld(), WoodFootstep,Hit.Location);
//			return;
//
//		case SurfaceType2: //Grass
//			UGameplayStatics::PlaySoundAtLocation(GetWorld(), GrassFootstep, Hit.Location);
//			return;
//
//		case SurfaceType3: //Concrete
//			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ConcreteFootstep, Hit.Location);
//			return;
//		}
//	}
//}