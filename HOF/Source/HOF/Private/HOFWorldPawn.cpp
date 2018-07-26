// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFWorldPawn.h"
#include "Engine/World.h"
#include "WorldBoardActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "HOFWorldCardActor.h"
#include "HOFPlayerState.h"
#include "GameData.h"
#include "HOFPlayerState.h"
#include "HOFWorldGameMode.h"
#include "HOFWorldPlayerController.h"


// Sets default values
AHOFWorldPawn::AHOFWorldPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHOFWorldPawn::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Cast<AHOFWorldPlayerController>(GetWorld()->GetPlayerControllerIterator()->Get());
	PlayerState = Cast<AHOFPlayerState>(PlayerController->PlayerState);
}

// Called every frame
void AHOFWorldPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHOFWorldPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHOFWorldPawn::SetPosition(int x, int y)
{
	m_Position.x = x;
	m_Position.y = y;

	auto playerState = Cast<AHOFPlayerState>(PlayerState);

	if (playerState)
	{
		playerState->SetWorldPawnPosition(x, y);
	}
}

void AHOFWorldPawn::SetLocation(FVector location)
{
	SetActorLocation(location);
}

void AHOFWorldPawn::SetRotation(FVector targetCardLocation)
{
	FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), targetCardLocation);

	SetActorRotation(newRotation);
}

