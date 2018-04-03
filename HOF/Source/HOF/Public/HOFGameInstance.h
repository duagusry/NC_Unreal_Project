// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayerData.h"
#include "GameData.h"
#include "HOFGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HOF_API UHOFGameInstance : public UGameInstance
{
	GENERATED_BODY()

public : 
	UHOFGameInstance();

	virtual void Init() override;
	
	TUniquePtr<FPlayerData> GetPlayerData() { return std::move(PlayerData); }
	EGameplayState::Type GetGamePlayState() { return GamePlayState; }
	
	void SetPlayerData(TUniquePtr<FPlayerData>& playerData) { PlayerData = std::move(playerData); }
	void SetGamePlayState(EGameplayState::Type state) { GamePlayState = state; }

	void SwitchToBattle(FString levelDir);

private : 
	TUniquePtr<FPlayerData> PlayerData;
	EGameplayState::Type GamePlayState;
};
