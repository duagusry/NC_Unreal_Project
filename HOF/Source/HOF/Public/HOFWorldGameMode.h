// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlayerData.h"
#include "GameData.h"
#include "HOFGameInstance.h"
#include "WorldBoardActor.h"
#include "HOFWorldPawn.h"
#include "HOFWorldGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HOF_API AHOFWorldGameMode : public AGameMode
{
	GENERATED_BODY()
	
public : 
	AHOFWorldGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void InitGameState() override;

	void OnTimerTick();
	
	void MovePawnTo(int32 x, int32 y);

public : 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AHOFWorldPawn> BP_WorldPawn;


private : 
	UHOFGameInstance* GameInstance;
	AHOFWorldBoardActor* WorldBoard;
	AHOFWorldPawn* WorldPawn;
	//int32 m_MapEventInfo[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT];
	
	UPROPERTY(EditAnywhere)
	int32 Counter;
	FTimerHandle countDownHandle;

};
