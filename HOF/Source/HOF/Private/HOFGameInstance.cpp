// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFGameInstance.h"
#include "Engine/World.h"

UHOFGameInstance::UHOFGameInstance()
{
	//�÷��̾� ������ ���� ����, �ʱ�ȭ
	PlayerData = MakeUnique<FPlayerData>();
}

void UHOFGameInstance::Init()
{
	Super::Init();

	GamePlayState = EGameplayState::Init;
}

void UHOFGameInstance::SwitchToBattle(FString levelDir)
{
	UE_LOG(LogClass, Warning, TEXT("Switch to BattleMode"));
	SetPlayerData(PlayerData);
	GetWorld()->ServerTravel(FString("/Game/Maps/HOFBattleLevel"));
}
