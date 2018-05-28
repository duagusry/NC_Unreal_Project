// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFAnimInstance.h"

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


