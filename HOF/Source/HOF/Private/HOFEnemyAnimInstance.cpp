// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFEnemyAnimInstance.h"
#include "HOF.h"
#include "HOFEnemyPawn.h"

UHOFEnemyAnimInstance::UHOFEnemyAnimInstance()
{
	VelocityAnim = 0.f;
}

void UHOFEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto pawn = Cast<AHOFEnemyPawn>(TryGetPawnOwner());

	if (pawn->IsRunning())
	{
		if (pawn->AnimationMap[EHOFEnemyAnimation::ANIM_RUN] != nullptr)
		{
			AB_LOG_CALLONLY(Warning);
			PlaySlotAnimationAsDynamicMontage(pawn->AnimationMap[EHOFEnemyAnimation::ANIM_RUN], TEXT("ANIM_RUN"), 0.1f, 0.1f, 1.0f, 5);
		}
	}
	else
	{
		if (pawn->AnimationMap[EHOFEnemyAnimation::ANIM_RUN] != nullptr)
		{
			AB_LOG_CALLONLY(Warning);
			PlaySlotAnimationAsDynamicMontage(pawn->AnimationMap[EHOFEnemyAnimation::ANIM_IDLE], TEXT("ANUM_IDLE"), 0.1f, 0.1f, 1.0f, 5);
		}
	}
	//if (Pawn && Pawn->IsValidLowLevel())
	//{
	//	VelocityAnim = Pawn->GetVelocity().Size();

	//	AHOFPlayerState* ABPlayerState = Cast<AHOFPlayerState>(Pawn->PlayerState);

	//	if (ABPlayerState)
	//	{
	//		//AB_LOG_CALLONLY(Warning);
	//		//CurrentStateAnim = ABPlayerState->CurrentStatePawn;
	//		//auto currentAnimSequence = Pawn->AnimationMap[CurrentStateAnim];
	//		//PlaySlotAnimationAsDynamicMontage(currentAnimSequence, TEXT("DefaultSlot"), 0.1f, 0.1f, 1.0f, 5);
	//	}
	//}
}

void UHOFEnemyAnimInstance::AnimNotify_AttackHit(UAnimNotify * Notify)
{
}

void UHOFEnemyAnimInstance::AnimNotify_AttackEnd(UAnimNotify * Notify)
{
}
