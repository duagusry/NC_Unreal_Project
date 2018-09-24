// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GameData.h"
#include "HOFPlayerState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EHOFCharacterState
{
	PLAYER_PEACE UMETA(DisplayName = "PLAYER_PEACE"),
	PLAYER_CHASE UMETA(DisplayName = "PLAYER_CHASE"),
	PLAYER_BATTLE UMETA(DisplayName = "PLAYER_BATTLE"),
	PLAYER_DEAD UMETA(DisplayName = "PLAYER_DEAD"),
};

UCLASS()
class HOF_API AHOFPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AHOFPlayerState();
	
	void SetPlayerData(BaseStructs::PlayerData playerData);

	BaseStructs::Position WorldPawnPosition;

	void SetState(EHOFCharacterState newState);
	inline EHOFCharacterState GetState() { return CurrentStatePawn; }

	void EatFood();
	void Heal(int32 heal);
	void GetDamage(int damage);
	void Die();
	inline bool IsAlive() const { return PlayerData.Alive; }

	inline void ModifyFood(int32 amount) { PlayerData.Food(amount); }
	inline void ModifyGold(int32 amount) { PlayerData.Gold(amount); }
	inline void ModifyMaxHP(int32 amount) { PlayerData.HP.ModifyMaxValue(amount); }
	inline void ModifyCurrentHP(float amount)
	{
		PlayerData.HP(amount);

		if (PlayerData.HP.CheckOnMinValue())
			Die();
	}

	const BaseStructs::Position& GetWorldPawnPosition() const { return WorldPawnPosition; }
	void SetWorldPawnPosition(int32 x, int32 y)
	{
		WorldPawnPosition.x = x;
		WorldPawnPosition.y = y;
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		TEnumAsByte<EHOFCharacterState> CurrentStatePawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Battle")
		uint32 bIsBattleInAction : 1;

	BaseStructs::PlayerData PlayerData;
};
