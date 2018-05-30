// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HOFPlayerController.generated.h"

class AHOFCharacter;

/**
 * 
 */
UCLASS()
class HOF_API AHOFPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AHOFPlayerController();

	virtual void PreInitializeComponents() override;

	virtual void PostInitializeComponents() override;

	virtual void BeginPlayingState() override;

	virtual void SetupInputComponent() override;

private:
	AHOFCharacter* character;

	float CurrentLeftRightVal;
	float CurrentUpDownVal;

	UFUNCTION()
		void MoveForward(float NewInputVal);

	UFUNCTION()
		void MoveRight(float NewInputval);

	UFUNCTION()
		void Turn(float NewInputval);

	UFUNCTION()
		void LookUp(float NewInputval);

	UFUNCTION()
		void JumpInput();

	UFUNCTION()
		void JumpIfNotInput();

	UFUNCTION()
		void Attack();

	UFUNCTION()
		void NotAttack();

	UFUNCTION()
		void SetStateToBattle();
};
