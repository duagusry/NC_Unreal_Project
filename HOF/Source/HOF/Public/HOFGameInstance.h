// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameData.h"
#include "HOFGameInstance.generated.h"

/**
 * 
 */

class EnemyData;
class AHOFPlayerState;

UCLASS()
class HOF_API UHOFGameInstance : public UGameInstance
{
	GENERATED_BODY()

public : 
	UHOFGameInstance();

	virtual void Init() override;
	
	EGameplayState::Type GetGamePlayState() { return GamePlayState; }
	
	void SetGamePlayState(EGameplayState::Type state) { GamePlayState = state; }

	void SwitchLevel(FString levelPath);

	void SetBattleData(const BaseStructs::BattleData& ref) { BattleData = ref; }
	TSharedPtr<EnemyData> GetEnemyData();
	bool IsEnemyDataAvailable();
	inline bool HasTransferData() { return TransferData.IsSet; }
	void SaveCurrentTransferData(const BaseStructs::TransferData& transferData, int32 returnDialogId);

	EGameplayState::Type GamePlayState;

	TSharedPtr<EnemyData> enemyData;		// enemyData can save ONLY one enemy info. It would be better saved as TMap (or TArray) via struct.
	BaseStructs::TransferData TransferData;
	BaseStructs::PlayerData PlayerData;
	BaseStructs::BattleData BattleData;
};
