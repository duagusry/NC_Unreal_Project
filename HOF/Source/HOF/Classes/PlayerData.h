#pragma once

#include "GameData.h"

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

class PlayerData
{
public : 
	static PlayerData* GetInstance()
	{
		if (!PlayerDataInstance)
			PlayerDataInstance = new PlayerData();

		return PlayerDataInstance;
	}

	void EatFood();

	void Heal(int32 heal);

	void GetDamage(int damage);

	void Die();

	bool IsAlive() { return Alive; }

	void GainFood(int32 amount) { Food += amount; }
	void LoseFood(int32 amount) { Food = Food < amount ? 0 : Food - amount; }
	void GainGold(int32 amount) { Gold += amount; }
	void LoseGold(int32 amount) { Gold = Gold < amount ? 0 : Gold - amount; }
	void GainMaxHealth(int32 amount) { MaxHealth += amount; }
	void LoseMaxHealth(int32 amount) { MaxHealth = MaxHealth < amount ? 0 : MaxHealth - amount; }
	void GainCurrentHealth(int32 amount) { CurrentHealth = CurrentHealth + amount > MaxHealth ? MaxHealth : CurrentHealth + amount; }
	void LoseCurrentHealth(int32 amount)
	{ 
		CurrentHealth = CurrentHealth < amount ? 0 : CurrentHealth - amount; 
		
		if (CurrentHealth <= 0)
			Die();
	}

	BaseStructs::Position GetWorldPawnPosition() const { return WorldPawnPosition; }
	void SetWorldPawnPosition(int32 x, int32 y)
	{
		WorldPawnPosition.x = x;
		WorldPawnPosition.y = y;
	}

private : 
	PlayerData();

private : 
	int32 Food;
	int32 Gold;
	int32 MaxHealth;
	int32 CurrentHealth;
	bool Alive;

	VariationData Var;
	BaseStructs::Position WorldPawnPosition;

	static PlayerData* PlayerDataInstance;
};

#define g_PlayerData PlayerData::GetInstance()