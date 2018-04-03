// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFSpectatorPawn.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/DefaultPawn.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h"

AHOFSpectatorPawn::AHOFSpectatorPawn()
{
	//얘도 자체 콜리전 값이 있어서 충돌 무시 설정을 해줘야 다른 액터를 클릭할 수 있음.
	GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	bAddDefaultMovementBindings = false;
}

void AHOFSpectatorPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AHOFSpectatorPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AHOFSpectatorPawn::MoveRight);
}

void AHOFSpectatorPawn::MoveForward(float Val)
{
	Super::MoveForward(Val);
}

void AHOFSpectatorPawn::MoveRight(float Val)
{
	Super::MoveRight(Val);
}
