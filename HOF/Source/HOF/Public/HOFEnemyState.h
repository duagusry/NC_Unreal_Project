// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData.h"
#include "HOFEnemyState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EHOFEnemyState
{
	ENEMY_PEACE UMETA(DisplayName = "ENEMY_PEACE"),
	ENEMY_CHASE UMETA(DisplayName = "ENEMY_CHASE"),
	ENEMY_BATTLE UMETA(DisplayName = "ENEMY_BATTLE"),
	ENEMY_DEAD UMETA(DisplayName = "ENEMY_DEAD"),
};

UCLASS()
class HOF_API UHOFEnemyState : public UObject
{
	GENERATED_BODY()

public:
	UHOFEnemyState();

	inline void SetState(EHOFEnemyState newState) { CurrentStatePawn = newState; }
	inline EHOFEnemyState GetState() { return CurrentStatePawn; }

public : 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		TEnumAsByte<EHOFEnemyState> CurrentStatePawn;
};
