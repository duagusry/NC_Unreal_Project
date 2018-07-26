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

	UPROPERTY()
		float MaxHP;

	UPROPERTY()
		float CurrentHP;

	UPROPERTY()
		int32 Food;

	UPROPERTY()
		int32 Gold;

	UPROPERTY()
		bool Alive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		TEnumAsByte<EHOFCharacterState> CurrentStatePawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Battle")
	uint32 bIsBattleInAction:1;

	void SetPlayerData(BaseStructs::PlayerData playerData);

	BaseStructs::Position WorldPawnPosition;

	void SetState(EHOFCharacterState newState);
	EHOFCharacterState GetState();

	void EatFood();
	void Heal(int32 heal);
	void GetDamage(int damage);
	void Die();
	inline bool IsAlive() const { return Alive; }

	inline void GainFood(int32 amount) { Food += amount; }
	inline void LoseFood(int32 amount) { Food = Food < amount ? 0 : Food - amount; }
	inline void GainGold(int32 amount) { Gold += amount; }
	inline void LoseGold(int32 amount) { Gold = Gold < amount ? 0 : Gold - amount; }
	inline void GainMaxHP(int32 amount) { MaxHP += amount; }
	inline void LoseMaxHP(int32 amount) { MaxHP = MaxHP < amount ? 0 : MaxHP - amount; }
	inline void GainCurrentHP(int32 amount) { CurrentHP = CurrentHP + amount > MaxHP ? MaxHP : CurrentHP + amount; }
	void LoseCurrentHP(int32 amount)
	{
		CurrentHP = CurrentHP < amount ? 0 : CurrentHP - amount;

		if (CurrentHP <= 0)
			Die();
	}

	const BaseStructs::Position& GetWorldPawnPosition() const { return WorldPawnPosition; }
	void SetWorldPawnPosition(int32 x, int32 y)
	{
		WorldPawnPosition.x = x;
		WorldPawnPosition.y = y;
	}
};
