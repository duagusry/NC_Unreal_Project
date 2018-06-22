// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "HOFPlayerState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EHOFCharacterState
{
	PEACE UMETA(DisplayName = "PEACE"),
	CHASE UMETA(DisplayName = "CHASE"),
	BATTLE UMETA(DisplayName = "BATTLE"),
	DEAD UMETA(DisplayName = "DEAD"),
};

UCLASS()
class HOF_API AHOFPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AHOFPlayerState();

	UPROPERTY()
		float MaxHP;

	UPROPERTY()
		float CurrentHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		TEnumAsByte<EHOFCharacterState> CurrentStatePawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Battle")
	uint32 bIsBattleInAction:1;

	void SetState(EHOFCharacterState newState);
	EHOFCharacterState GetState();
};
