// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFBattleGameState.h"
#include "HOF.h"

AHOFBattleGameState::AHOFBattleGameState() : enemyCount(0)
{
}

void AHOFBattleGameState::SetEnemyCount(int initCount)
{
	AB_LOG(Warning, TEXT("Set enemyCount %d in BattleGameState"), initCount);
	enemyCount += initCount;
}

bool AHOFBattleGameState::AreEnemiesClear()
{
	return enemyCount == 0;
}

void AHOFBattleGameState::DecreaseEnemyCount()
{
	AB_LOG(Warning, TEXT("Enemy's down."));
	if(enemyCount > 0)
		enemyCount--;
}
