// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFGameInstance.h"
#include "PlayerData.h"
#include "EnemyData.h"
#include "Engine/World.h"

UHOFGameInstance::UHOFGameInstance() : 
	playerData(MakeShared<PlayerData>(*(PlayerData::GetInstance()))), 
	enemyData(MakeShared<EnemyData>())
{
}

void UHOFGameInstance::Init()
{
	Super::Init();

	GamePlayState = EGameplayState::Init;
}

void UHOFGameInstance::SwitchLevel(FString levelPath)
{
	UE_LOG(LogClass, Warning, TEXT("Switch to BattleMode"));
	GetWorld()->ServerTravel(levelPath);
}

TSharedPtr<PlayerData> UHOFGameInstance::GetPlayerData()
{
	return playerData;
}

TSharedPtr<EnemyData> UHOFGameInstance::GetEnemyData()
{
	return enemyData;
}

bool UHOFGameInstance::IsEnemyDataAvailable()
{
	return enemyData.IsValid();
}
