// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFGameInstance.h"
#include "EnemyResources.h"
#include "HOFEnemyPawn.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UHOFGameInstance::UHOFGameInstance()
{
}

void UHOFGameInstance::Init()
{
	Super::Init();
}

void UHOFGameInstance::SwitchLevel(FString levelPath)
{
	UE_LOG(LogClass, Warning, TEXT("Switch to BattleMode"));
	GetWorld()->ServerTravel(levelPath);
}

void UHOFGameInstance::SaveCurrentWorldStatusData(const BaseStructs::WorldStatusData& worldStatusData)
{
	WorldStatusData = worldStatusData;
	WorldStatusData.IsSet = true;
}
