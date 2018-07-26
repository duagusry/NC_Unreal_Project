// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameData.h"
#include "HOFGameInstance.generated.h"

/**
 * 
 */

// BattleMode로 넘어갈 때 전달할 파라미터
struct BattleTransferParameter
{
	TMap<FString, int32> SpawnInfo;
	int32 ReturnDialog;
};

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

	void SetBattleParameter(const BattleTransferParameter& ref) { BattleParameter = ref; }
	TSharedPtr<EnemyData> GetEnemyData();
	bool IsEnemyDataAvailable();
	inline bool HasTransferData() { return TransferData.IsSet; }
	void SaveCurrentTransferData(const BaseStructs::TransferData& transferData, int32 returnDialogId);

	EGameplayState::Type GamePlayState;

	BattleTransferParameter BattleParameter;
	TSharedPtr<EnemyData> enemyData;
	BaseStructs::TransferData TransferData;
	BaseStructs::PlayerData PlayerData;
};
