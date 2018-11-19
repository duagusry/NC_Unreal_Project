// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFGameInstance.h"
#include "EnemyResources.h"
#include "HOFEnemyPawn.h"
#include "Engine/World.h"
#include "HOFItemResource.h"
#include "Kismet/GameplayStatics.h"

UHOFGameInstance::UHOFGameInstance()
{
	PlayerData = BaseStructs::PlayerData{ BaseStructs::Stat<float>(100, 100, 0), BaseStructs::Stat<int32>(30, 100, 0), BaseStructs::Stat<int32>(10, 1000, 0), true };
	EquipData = TSharedPtr<AHOFEquipStatus>(CreateDefaultSubobject<AHOFEquipStatus>(TEXT("EquipData")));
	ItemResource = NewObject<UItemResource>();
}

void UHOFGameInstance::Init()
{
	Super::Init(); 
	ItemResource->Parse(FPaths::ProjectDir() + L"Resource\\Xml\\WeaponItem.xml");
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
