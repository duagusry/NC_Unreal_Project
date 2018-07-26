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
	m_X = x;
	m_Y = y;
	m_Revealed = false;
	m_IsVisited = false;
	IsAdjacentToPawn = false;
	m_CardEvent = g_CardEvent->GetCardEventFromId(id);
	if (!m_CardEvent.GetID())
		return;

	m_Title = FText::FromString(m_CardEvent.GetTitle());
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
	if (m_IsVisited)
		return;

	if (IsAdjacentToPawn)
	{
		UE_LOG(LogClass, Warning, TEXT("Card selected -> x : %d, y : %d"), m_X, m_Y);

		Cast<AHOFWorldGameMode>(GetWorld()->GetAuthGameMode())->MovePawnTo(m_X, m_Y);

		Visit();
	}
}

void AHOFWorldCardActor::TextEvent(int32 returnDialog)
{
	Cast<AHOFWorldPlayerController>(GetWorld()->GetFirstPlayerController())->ShowEventWidget(m_CardEvent.GetID(), this, returnDialog);
}

void AHOFWorldCardActor::BattleEvent(/* TMap<int, int>& spawnList, int mapNumber*/ )
{
	//레벨 이동할 때 파라미터로 넘겨야되는데 방법 찾아봐야됨.
	//GameInstance에 다 넣어놓고 쓸수도 있을거같은데 그건 좀..

	Cast<UHOFGameInstance>(GetGameInstance())->SwitchLevel(FString("/Game/Maps/HOFBattleLevel"));
}

void AHOFWorldCardActor::SetAdjacency(bool isAdjacent)
{
	IsAdjacentToPawn = isAdjacent;
}

void AHOFWorldCardActor::Reveal()
{
	m_Revealed = true;

	if (m_Revealed)
	{
		FRotator newRotation = GetActorRotation();
		newRotation.Roll = -180;
		SetActorRotation(newRotation);
	}
}

void AHOFWorldCardActor::Visit(int32 returnDialog)
{
	m_IsVisited = true;

	if (returnDialog == 1)
	{
		auto PlayerController = Cast<AHOFWorldPlayerController>(GetWorld()->GetFirstPlayerController());
		Cast<AHOFPlayerState>(PlayerController->PlayerState)->EatFood();
	}

	Reveal();
	TextEvent(returnDialog);
	//BattleEvent();
}

void AHOFWorldCardActor::SetCardDataFromTransferData(const BaseStructs::TransferData::WorldSlotDataStruct & transferData)
{
	if (transferData.IsRevealed)
		Reveal();

	m_IsVisited = transferData.IsVisited;
}

