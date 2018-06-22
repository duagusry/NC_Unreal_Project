// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFAnimInstance.h"
#include "HOFCharacter.h"

UHOFAnimInstance::UHOFAnimInstance()
{
	VelocityAnim = 0.0f;
}

void UHOFAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
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

void UHOFAnimInstance::AnimNotify_AttackHit(UAnimNotify * Notify)
{
	AHOFCharacter *HOFCharacter = Cast<AHOFCharacter>(TryGetPawnOwner());

	if (HOFCharacter && HOFCharacter->IsValidLowLevel())
	{
		HOFCharacter->AttackHit();
	}
}

void UHOFAnimInstance::AnimNotify_AttackEnd(UAnimNotify * Notify)
{
	AHOFCharacter *HOFCharacter = Cast<AHOFCharacter>(TryGetPawnOwner());

	if (HOFCharacter && HOFCharacter->IsValidLowLevel())
	{
		AHOFPlayerState* HOFPlayerState = Cast<AHOFPlayerState>(HOFCharacter->PlayerState);
		if(HOFPlayerState)
			HOFPlayerState->SetState(EHOFCharacterState::PEACE);
	}
}


