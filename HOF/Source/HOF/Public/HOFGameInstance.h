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
	int32 EnemyCount;
	int32 ReturnDialog;
};

class EnemyData;

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

private : 
	EGameplayState::Type GamePlayState;

	BattleTransferParameter BattleParameter;
	TSharedPtr<EnemyData> enemyData;
};
