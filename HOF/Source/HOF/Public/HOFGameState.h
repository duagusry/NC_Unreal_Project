// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "HOFGameState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EHOFGameState
{
	GAME_INIT UMETA(DisplayName = "GAME_INIT"),
	GAME_MENU UMETA(DisplayName = "GAME_MENU"),
	GAME_WORLD UMETA(DisplayName = "GAME_WORLD"),
	GAME_DIALOG UMETA(DisplayName = "GAME_DIALOG"),
	GAME_GAMBIT UMETA(DisplayName = "GAME_GAMBIT"),
	GAME_BATTLE UMETA(DisplayName = "GAME_BATTLE"),
	GAME_DEAD UMETA(DisplayName = "GAME_DEAD"),
	GAME_CLEAR UMETA(DisplayName = "GAME_CLEAR"),
};

UCLASS()
class HOF_API AHOFGameState : public AGameState
{
public : 
	GENERATED_BODY()

	AHOFGameState();

	void GameStart();

	void SetState(EHOFGameState newState);
	inline EHOFGameState GetState() { return CurrentGameState; }
	
private : 
	void OnGameStart();
	void OnDialogEvent();
	void OnBattleEvent();
	void OnPlayerDead();

public : 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EHOFGameState> CurrentGameState;
};
