// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFPawnAnimInstance.h"
#include "HOFCharacter.h"

UHOFPawnAnimInstance::UHOFPawnAnimInstance()
{
	VelocityAnim = 0.0f;
}

void UHOFPawnAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	APawn* Pawn = TryGetPawnOwner();

	if (Pawn && Pawn->IsValidLowLevel())
	{
		VelocityAnim = Pawn->GetVelocity().Size();

		AHOFPlayerState* ABPlayerState = Cast<AHOFPlayerState>(Pawn->PlayerState);

		if (ABPlayerState)
			CurrentStateAnim = ABPlayerState->CurrentStatePawn;
	}
}

void UHOFPawnAnimInstance::AnimNotify_AttackHit(UAnimNotify * Notify)
{
	AHOFCharacter *HOFCharacter = Cast<AHOFCharacter>(TryGetPawnOwner());

	if (HOFCharacter && HOFCharacter->IsValidLowLevel())
	{
		HOFCharacter->AttackHit();
	}
}

void UHOFPawnAnimInstance::AnimNotify_AttackEnd(UAnimNotify * Notify)
{
	AHOFCharacter *HOFCharacter = Cast<AHOFCharacter>(TryGetPawnOwner());

	if (HOFCharacter && HOFCharacter->IsValidLowLevel())
	{
		AHOFPlayerState* HOFPlayerState = Cast<AHOFPlayerState>(HOFCharacter->PlayerState);
		if (HOFPlayerState)
			HOFPlayerState->SetState(EHOFCharacterState::PLAYER_PEACE);
	}
}

