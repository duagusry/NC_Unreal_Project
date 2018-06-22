// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HOFPlayerState.h"
#include "HOFEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HOF_API UHOFEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UHOFEnemyAnimInstance();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pawn")
		float VelocityAnim;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		TEnumAsByte<EHOFCharacterState> CurrentStateAnim;

	UFUNCTION()
		void AnimNotify_AttackHit(UAnimNotify *Notify);

	UFUNCTION()
		void AnimNotify_AttackEnd(UAnimNotify *Notify);
};
