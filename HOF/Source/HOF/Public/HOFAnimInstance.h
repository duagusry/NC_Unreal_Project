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
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) { Super::NativeUpdateAnimation(DeltaSeconds); }
	
	UFUNCTION()
		virtual void AnimNotify_AttackHit(UAnimNotify *Notify) { }

	UFUNCTION()
		virtual void AnimNotify_AttackEnd(UAnimNotify *Notify) { }
	
};
