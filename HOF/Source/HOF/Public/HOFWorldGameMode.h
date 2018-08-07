// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameData.h"
#include "HOFGameInstance.h"
#include "WorldBoardActor.h"
#include "HOFWorldPawn.h"
#include "HOFWorldGameMode.generated.h"

class AHOFWorldPawn;
class UHOFGameInstance;
class AHOFWorldBoardActor;

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

	void InitWorld(int32 MapEventInfo[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT]);

	void LoadWorld(int32 MapEventInfo[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT]);
		
	void MovePawnTo(int32 x, int32 y);

	void HandleRevealEvent(int32 Amount);

	void SpawnPawnOnBoard(int32 x, int32 y);

	void InitWorldBoardPosition(int32 x, int32 y);

	BaseStructs::WorldStatusData AssignWorldStatusData(int32 returnDialogId);

public : 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AHOFWorldPawn> BP_WorldPawn;

private : 
	UHOFGameInstance* GameInstance;
	AHOFWorldBoardActor* WorldBoard;
	AHOFWorldPawn* WorldPawn;
	
};
