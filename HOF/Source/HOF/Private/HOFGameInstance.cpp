// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFGameInstance.h"
#include "EnemyData.h"
#include "HOFEnemyPawn.h"
#include "Engine/World.h"

UHOFGameInstance::UHOFGameInstance() : 
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

TSharedPtr<EnemyData> UHOFGameInstance::GetEnemyData()
{
	return enemyData;
}

bool UHOFGameInstance::IsEnemyDataAvailable()
{
	return enemyData.IsValid() && enemyData->enemySpecy;
}
