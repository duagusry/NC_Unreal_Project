// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HOFPlayerState.h"
#include "HOFEnemyAnimInstance.generated.h"

/**
 * 
 */

class AHOFEnemyPawn;

UCLASS()
class HOF_API UHOFEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UHOFEnemyAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
		void AnimNotify_AttackHit(UAnimNotify *Notify);

	UFUNCTION()
		void AnimNotify_AttackEnd(UAnimNotify *Notify);

	UFUNCTION(BlueprintCallable)
		bool IsCurrentStateAnimSameAs(EHOFCharacterState state);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		TEnumAsByte<EHOFCharacterState> CurrentStateAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		bool IsRunning;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		AHOFEnemyPawn *Pawn;

protected:
	// Called when the game starts or when spawned
	virtual void NativeBeginPlay() override;
};
