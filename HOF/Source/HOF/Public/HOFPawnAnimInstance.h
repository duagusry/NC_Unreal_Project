// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HOFAnimInstance.h"
#include "HOFPawnAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HOF_API UHOFPawnAnimInstance : public UHOFAnimInstance
{
	GENERATED_BODY()

public : 
	UHOFPawnAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
		virtual void AnimNotify_AttackHit(UAnimNotify *Notify) override;

	UFUNCTION()
		virtual void AnimNotify_AttackEnd(UAnimNotify *Notify) override;

public : 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pawn")
		float VelocityAnim;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		TEnumAsByte<EHOFCharacterState> CurrentStateAnim;
	
};
