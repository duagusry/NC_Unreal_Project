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
	
	EGameplayState::Type GetGamePlayState() { return GamePlayState; }
	
	void SetGamePlayState(EGameplayState::Type state) { GamePlayState = state; }

	void SwitchToBattle(FString levelDir);

private : 
	EGameplayState::Type GamePlayState;
};
