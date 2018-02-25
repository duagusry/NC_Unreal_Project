#pragma once

#include "PlayerData.generated.h"

//버프, 이벤트 등으로 인한 변동치 데이터
struct VariationData
{
	int32 FoodConsumption = 1;
	int32 HealByFood = 8;
	int32 DamageByFood = 24;

	//하위로 GainData와 LostData를 구분하는것도 좋을지도..

	//GainData(+수치) : 금 획득량, 식량 획득량, 회복량,, ...
	//LostData(-수치) : 금 손실량, 식량 손실(소비)량, 데미지, ...
};

USTRUCT()
struct FPlayerData
{
	GENERATED_BODY()

public : 
	FPlayerData()
	{
		Food = 10;
		Gold = 30;
		MaxHealth = 100;
		CurrentHealth = 100;
		Alive = true;

		//Health 관련된 부분은 lock 필요할듯. (전투상황)
	}

	void EatFood()
	{
		//식량이 모자라면 데미지를 받음
		if (Food < Var.FoodConsumption)
		{
			Food = 0;
			GetDamage(Var.DamageByFood);
			
			return;
		}

		Food -= Var.FoodConsumption;
		UE_LOG(LogClass, Warning, TEXT("Food Consumed, Current Food : %d"), Food);

		Heal(Var.HealByFood);
	}

	void Heal(int32 heal)
	{
		int32 TempHealth = CurrentHealth;

		CurrentHealth += heal;
		if (CurrentHealth > MaxHealth)
			CurrentHealth = MaxHealth;
		UE_LOG(LogClass, Warning, TEXT("Healed, %d -> %d / %d(max)"), TempHealth, CurrentHealth, MaxHealth);
	}

	void GetDamage(int damage)
	{
		int32 TempHealth = CurrentHealth;

		CurrentHealth -= damage;
		if (CurrentHealth <= 0)
			CurrentHealth = 0;
		UE_LOG(LogClass, Warning, TEXT("GetDamage, %d -> %d / %d(max)"), TempHealth, CurrentHealth, MaxHealth);

		if (CurrentHealth <= 0)
			Die();
	}

	void Die()
	{
		Alive = false;
		UE_LOG(LogClass, Warning, TEXT("YOU DIED"));
	}

	bool IsAlive() { return Alive; }

private : 
	int32 Food;
	int32 Gold;
	int32 MaxHealth;
	int32 CurrentHealth;
	bool Alive;

	VariationData Var;

};