// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFWorldCardActor.h"
#include "Engine/World.h"
#include "HOFGameInstance.h"


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
	m_CardEvent = g_CardEvent->GetCardEventFromId(id);
	if (!m_CardEvent.GetID())
		return;
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
	UE_LOG(LogClass, Warning, TEXT("Card selected -> x : %d, y : %d"), m_X, m_Y);

	//BattleEvent();
}

void AHOFWorldCardActor::BattleEvent(/* TMap<int, int>& spawnList, int mapNumber*/ )
{
	//레벨 이동할 때 파라미터로 넘겨야되는데 방법 찾아봐야됨.
	//GameInstance에 다 넣어놓고 쓸수도 있을거같은데 그건 좀..

	Cast<UHOFGameInstance>(GetGameInstance())->SwitchToBattle(FString("/Game/Maps/HOFBattleLevel"));
}

