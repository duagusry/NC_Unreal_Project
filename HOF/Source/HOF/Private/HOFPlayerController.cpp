// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFPlayerController.h"
#include "HOF.h"
#include "HOFCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

AHOFPlayerController::AHOFPlayerController()
{
	bShowMouseCursor = true;
}

void AHOFPlayerController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	AB_LOG(Warning, TEXT("%"), GetPawn() ? *GetPawn()->GetClass()->GetFullName() : TEXT("NoPawn"));
}

void AHOFPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AB_LOG(Warning, TEXT("%s"), GetPawn() ? *GetPawn()->GetClass()->GetFullName() : TEXT("NoPawn"));
}

// Called whenthe game starts or when spawned 
void AHOFPlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();
	CurrentMouseCursor = EMouseCursor::Crosshairs;

	character = Cast<AHOFCharacter>(this->GetCharacter());
	if (character == NULL)
		AB_LOG(Warning, TEXT("Can't load a pawn. Controller should possesss a apawn."));
}

void AHOFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//InputComponent->BindAxis("MoveRight", this, &AABPlayerController::LeftRightInput);
	//InputComponent->BindAxis("MoveForward", this, &AABPlayerController::UpDownInput);

	InputComponent->BindAxis("MoveForward", this, &AHOFPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AHOFPlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &AHOFPlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &AHOFPlayerController::LookUp);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AHOFPlayerController::JumpInput);
	InputComponent->BindAction("Jump", IE_Released, this, &AHOFPlayerController::JumpIfNotInput);
	InputComponent->BindAction("Attack", IE_Pressed, this, &AHOFPlayerController::Attack);
	InputComponent->BindAction("Attack", IE_Released, this, &AHOFPlayerController::NotAttack);

	
}

void AHOFPlayerController::MoveForward(float NewInputVal)
{
	if (NewInputVal != 0.0f)
	{
		// find out which way is forward
		FRotator Rotation = character->Camera->GetComponentRotation();
		// Limit pitch when walking or falling
		if (character->GetCharacterMovement()->IsMovingOnGround() || character->GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		character->AddMovementInput(Direction, NewInputVal);

		const FRotator curRotation = character->GetActorRotation();
		const FVector XScaledCurRotation = FRotationMatrix(curRotation).GetScaledAxis(EAxis::X);
		FRotator newRotation = UKismetMathLibrary::MakeRotFromX(FVector(NewInputVal, XScaledCurRotation.Y, 0));
		SetControlRotation(newRotation);
	}
}

void AHOFPlayerController::MoveRight(float NewInputVal)
{
	if (NewInputVal != 0.0f)
	{
		FRotator rotation = character->Camera->GetComponentRotation(); //Controller->GetControlRotation();
		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::Y);
		character->AddMovementInput(direction, NewInputVal);

		const FRotator curRotation = character->GetActorRotation();
		const FVector XScaledCurRotation = FRotationMatrix(curRotation).GetScaledAxis(EAxis::X);
		FRotator newRotation = UKismetMathLibrary::MakeRotFromX(FVector(XScaledCurRotation.X, NewInputVal, 0));
		SetControlRotation(newRotation);
	}
}

void AHOFPlayerController::Turn(float NewInputval)
{
	character->AddControllerYawInput(NewInputval);
}

void AHOFPlayerController::LookUp(float NewinputVal)
{
	character->AddControllerPitchInput(NewinputVal);
}

void AHOFPlayerController::JumpInput()
{
	character->bPressedJump = true;
}

void AHOFPlayerController::JumpIfNotInput()
{
	character->bPressedJump = false;
}

void AHOFPlayerController::Attack()
{
	character->isAttacking = true;
}

void AHOFPlayerController::NotAttack()
{
	character->isAttacking = false;
}



