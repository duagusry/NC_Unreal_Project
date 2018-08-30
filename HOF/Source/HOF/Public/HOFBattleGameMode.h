// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameData.h"
#include "HOFGameInstance.h"
#include "HOFBattleGameMode.generated.h"

/**
 * 
 */

class AHOFEnemyPawn;

UCLASS()
class HOF_API AHOFBattleGameMode : public AGameMode
{
	GENERATED_BODY()
	
public : 
	AHOFBattleGameMode();
	void OnPlayerDead();
	void OnEnemyDead();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void InitGameState() override;

private:
	void InitializeEnemyPawns();
	void InitializeEnemyPawn(const TPair<FString, int32> &spawnInfo);
	void SpawnEnemyPawn(TSubclassOf<AHOFEnemyPawn> specy, int number);
	void SwitchToWorldLevel();

private : 
	UHOFGameInstance* GameInstance;
	FTimerHandle countDownHandle;
	TArray<AHOFEnemyPawn*> enemyPawns;
	//PlayerController도 여기 있어야할것같음.
};
