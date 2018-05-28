// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HOFPlayerState.h"
#include "HOFAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HOF_API UHOFAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UHOFAnimInstance();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pawn")
		float VelocityAnim;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		TEnumAsByte<HOFCharacterState> CurrentStateAnim;
};
