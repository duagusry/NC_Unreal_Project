// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFBattleGameMode.h"
#include "Engine/World.h"
#include"Runtime/Engine/Public/TimerManager.h"

//생성자는 언리얼에디터 처음 켤 때 불리기때문에 여기서 무슨 짓을 하면 대부분의 다른 객체들이 생성 안된 nullptr여서 에러 날 확률이 높음.
//초기화는 게임이 시작할때 호출되는 BeginPlay에서..
//그러면 생성자에서는 도대체 무슨짓을 할 수 있을까..
AHOFBattleGameMode::AHOFBattleGameMode()
{
	UE_LOG(LogClass, Warning, TEXT("BattleGameMode Start"));
}

void AHOFBattleGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UHOFGameInstance>(GetGameInstance());

	Counter = 3;
	GetWorldTimerManager().SetTimer(countDownHandle, this, &AHOFBattleGameMode::OnTimerTick, 1.0f, true);

	//PlayerData 이전받음
	PlayerData = GameInstance->GetPlayerData();

	GameInstance->SetGamePlayState(EGameplayState::Battle);
}

void AHOFBattleGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHOFBattleGameMode::InitGameState()
{
	Super::InitGameState();
}

void AHOFBattleGameMode::OnTimerTick()
{
	--Counter;

	//타이머 만료시 WorldLevel 오픈
	if (Counter < 1)
	{
		PlayerData->EatFood();

		UE_LOG(LogClass, Warning, TEXT("Alive? %s"), PlayerData->IsAlive() ? TEXT("Alive") : TEXT("Dead"));

		GameInstance->SetPlayerData(PlayerData);
		GetWorld()->ServerTravel(FString("/Game/Maps/HOFWorldLevel"));
		GetWorldTimerManager().ClearTimer(countDownHandle);
	}
}
