// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFEnemyAnimInstance.h"
#include "HOF.h"
#include "HOFEnemyPawn.h"

void UHOFEnemyAnimInstance::NativeBeginPlay()
{
	AB_LOG(Warning, TEXT("BeginPlay in EnemyAnimInstance"))
}

void UHOFEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Pawn == nullptr)
		Pawn = Cast<AHOFEnemyPawn>(TryGetPawnOwner());
	else
	{
		if (Pawn->IsRunning())
			IsRunning = true;

		CurrentStateAnim = Pawn->GetEnemyState()->CurrentStatePawn;
	}
}

void UHOFEnemyAnimInstance::AnimNotify_AttackHit(UAnimNotify * Notify)
{
	AHOFEnemyPawn *HOFEnemyPawn = Cast<AHOFEnemyPawn>(TryGetPawnOwner());

	if (HOFEnemyPawn && HOFEnemyPawn->IsValidLowLevel())
	{
		HOFEnemyPawn->AttackHit();
	}
}

void UHOFEnemyAnimInstance::AnimNotify_AttackEnd(UAnimNotify * Notify)
{
	AHOFEnemyPawn *HOFEnemyPawn = Cast<AHOFEnemyPawn>(TryGetPawnOwner());

	if (HOFEnemyPawn && HOFEnemyPawn->IsValidLowLevel())
	{
		HOFEnemyPawn->GetEnemyState()->SetState(EHOFEnemyState::ENEMY_PEACE);
	}
}

bool UHOFEnemyAnimInstance::IsCurrentStateAnimSameAs(EHOFEnemyState state)
{
	if(!CurrentStateAnim)
		return false;

	return CurrentStateAnim == state;
}
