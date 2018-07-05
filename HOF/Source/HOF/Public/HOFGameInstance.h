// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameData.h"
#include "HOFGameInstance.generated.h"

/**
 * 
 */

class PlayerData;
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

	TSharedPtr<PlayerData> GetPlayerData();
	TSharedPtr<EnemyData> GetEnemyData();
	bool IsEnemyDataAvailable();

private : 
	EGameplayState::Type GamePlayState;
	TSharedPtr<PlayerData> playerData;
	TSharedPtr<EnemyData> enemyData;
};
