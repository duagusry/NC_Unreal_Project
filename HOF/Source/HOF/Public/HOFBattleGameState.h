// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "HOFBattleGameState.generated.h"

/**
 * 
 */
UCLASS()
class HOF_API AHOFBattleGameState : public AGameState
{
	GENERATED_BODY()
public:
	AHOFBattleGameState();
	void SetEnemyCount(int initCount);
	bool AreEnemiesClear();
	void DecreaseEnemyCount();
	
private:
	int enemyCount;
};
