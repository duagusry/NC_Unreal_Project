// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "HOFPlayerState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum HOFCharacterState
{
	PEACE UMETA(DisplayName = "PEADE"),
	BATTLE UMETA(DisplayName = "BATTLE"),
	DEAD UMETA(DisplayName = "DEAD"),
};

UCLASS()
class HOF_API AHOFPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	UPROPERTY()
		int32 CharacterType;

	UPROPERTY()
		float MaxHP;

	UPROPERTY()
		float CurrentHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		TEnumAsByte<HOFCharacterState> CurrentStatePawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Battle")
	uint32 bIsBattleInAction:1;

	void SetState(HOFCharacterState newState);
};
