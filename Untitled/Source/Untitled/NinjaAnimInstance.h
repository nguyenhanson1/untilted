// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NinjaAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNTITLED_API UNinjaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	
	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimProperties();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MovementDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class AUntitledCharacter* Ninja;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class USoundBase* WoodFootstep;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class USoundBase* GrassFootstep;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class USoundBase* ConcreteFootstep;
};
