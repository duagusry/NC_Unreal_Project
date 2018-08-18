// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFWorldCardActor.h"
#include "Engine/World.h"
#include "HOFGameInstance.h"
#include "GameFramework/Actor.h"
#include "HOFWorldGameMode.h"
#include "HOFWorldPlayerController.h"
#include "HOFPlayerState.h"


// Sets default values
AHOFWorldCardActor::AHOFWorldCardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AHOFWorldCardActor::Init(int32 id, int32 x, int32 y)
{
	X = x;
	Y = y;
	Revealed = false;
	IsVisited = false;
	IsAdjacentToPawn = false;
	CardEvent = g_CardEvent->GetCardEventFromId(id);
	if (!CardEvent.GetID())
		return;

	Title = FText::FromString(CardEvent.GetTitle());
}

// Called when the game starts or when spawned
void AHOFWorldCardActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHOFWorldCardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHOFWorldCardActor::OnInputTap_Implementation()
{
	if (IsVisited)
		return;

	if (IsAdjacentToPawn)
	{
		UE_LOG(LogClass, Warning, TEXT("Card selected -> x : %d, y : %d"), X, Y);

		Cast<AHOFWorldGameMode>(GetWorld()->GetAuthGameMode())->MovePawnTo(X, Y);

		Visit();
	}
}

void AHOFWorldCardActor::TextEvent(int32 returnDialog)
{
	Cast<AHOFWorldPlayerController>(GetWorld()->GetFirstPlayerController())->ShowEventWidget(CardEvent.GetID(), this, returnDialog);
}

void AHOFWorldCardActor::SetAdjacency(bool isAdjacent)
{
	IsAdjacentToPawn = isAdjacent;
}

void AHOFWorldCardActor::Reveal()
{
	Revealed = true;

	if (Revealed)
	{
		FRotator newRotation = GetActorRotation();
		newRotation.Roll = -180;
		SetActorRotation(newRotation);
	}
}

void AHOFWorldCardActor::Visit(int32 returnDialog)
{
	IsVisited = true;

	if (returnDialog == 1)
	{
		auto PlayerController = Cast<AHOFWorldPlayerController>(GetWorld()->GetFirstPlayerController());
		Cast<AHOFPlayerState>(PlayerController->PlayerState)->EatFood();
	}

	Reveal();
	TextEvent(returnDialog);
	//BattleEvent();
}

void AHOFWorldCardActor::SetCardDataFromWorldStatusData(const BaseStructs::WorldStatusData::WorldSlotDataStruct & worldStatusData)
{
	if (worldStatusData.IsRevealed)
		Reveal();

	IsVisited = worldStatusData.IsVisited;
}

