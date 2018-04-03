// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "HOFSpectatorPawn.generated.h"

/**
*
*/
UCLASS(Blueprintable, BlueprintType)
class AHOFSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	AHOFSpectatorPawn();

	/** Add custom key bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/** event call on move forward input */
	virtual void MoveForward(float Val) override;

	/** event call on strafe right input */
	virtual void MoveRight(float Val) override;
};
