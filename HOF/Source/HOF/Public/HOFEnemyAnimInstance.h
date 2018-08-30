// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HOFAnimInstance.h"
#include "HOFEnemyState.h"
#include "HOFEnemyAnimInstance.generated.h"

/**
 * 
 */

class AHOFEnemyPawn;

UCLASS()
class HOF_API UHOFEnemyAnimInstance : public UHOFAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
		virtual void AnimNotify_AttackHit(UAnimNotify *Notify) override;

	UFUNCTION()
		virtual void AnimNotify_AttackEnd(UAnimNotify *Notify) override;

	UFUNCTION(BlueprintCallable)
		virtual bool IsCurrentStateAnimSameAs(EHOFEnemyState state);

public : 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		bool IsRunning;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		AHOFEnemyPawn *Pawn;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		TEnumAsByte<EHOFEnemyState> CurrentStateAnim;

protected:
	// Called when the game starts or when spawned
	virtual void NativeBeginPlay() override;
};
