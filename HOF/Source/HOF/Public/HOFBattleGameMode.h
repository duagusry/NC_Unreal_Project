// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlayerData.h"
#include "GameData.h"
#include "HOFGameInstance.h"
#include "HOFBattleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HOF_API AHOFBattleGameMode : public AGameMode
{
	GENERATED_BODY()
	
public : 
	AHOFBattleGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void InitGameState() override;

	void OnTimerTick();

private : 
	void InitializeEnemyPawn();
	void SpawnEnemyPawn(UClass *specy, int number);
	UHOFGameInstance* GameInstance;

	//PlayerController도 여기 있어야할것같음.
	

	UPROPERTY(EditAnywhere)
	int32 Counter;
	FTimerHandle countDownHandle;

};
