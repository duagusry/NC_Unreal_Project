// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameData.h"
#include "HOFEquipStatus.h"
#include "HOFGameInstance.generated.h"

/**
 * 
 */

class EnemyResources;
class AHOFPlayerState;
class UItemResource;

UCLASS()
class HOF_API UHOFGameInstance : public UGameInstance
{
	GENERATED_BODY()

public : 
	UHOFGameInstance();

	virtual void Init() override;
	
	void SwitchLevel(FString levelPath);

	void SetBattleData(const BaseStructs::BattleData& ref) { BattleData.Reset();  BattleData = ref; }
	inline bool HasWorldStatusData() { return WorldStatusData.IsSet; }
	void SaveCurrentWorldStatusData(const BaseStructs::WorldStatusData& transferData);

	//TSharedPtr<EnemyResources> EnemyResources;		// EnemyResources can save ONLY one enemy info. It would be better saved as TMap (or TArray) via struct.
	BaseStructs::WorldStatusData WorldStatusData;
	BaseStructs::PlayerData PlayerData;
	BaseStructs::BattleData BattleData;
	AHOFEquipStatus* EquipData;
	UPROPERTY()
	UItemResource *ItemResource;
};
