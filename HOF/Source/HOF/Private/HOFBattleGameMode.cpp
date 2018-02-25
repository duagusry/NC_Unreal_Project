// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFBattleGameMode.h"
#include "Engine/World.h"
#include"Runtime/Engine/Public/TimerManager.h"

//�����ڴ� �𸮾󿡵��� ó�� �� �� �Ҹ��⶧���� ���⼭ ���� ���� �ϸ� ��κ��� �ٸ� ��ü���� ���� �ȵ� nullptr���� ���� �� Ȯ���� ����.
//�ʱ�ȭ�� ������ �����Ҷ� ȣ��Ǵ� BeginPlay����..
//�׷��� �����ڿ����� ����ü �������� �� �� ������..
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

	//PlayerData ��������
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

	//Ÿ�̸� ����� WorldLevel ����
	if (Counter < 1)
	{
		PlayerData->EatFood();

		UE_LOG(LogClass, Warning, TEXT("Alive? %s"), PlayerData->IsAlive() ? TEXT("Alive") : TEXT("Dead"));

		GameInstance->SetPlayerData(PlayerData);
		GetWorld()->ServerTravel(FString("/Game/Maps/HOFWorldLevel"));
		GetWorldTimerManager().ClearTimer(countDownHandle);
	}
}
