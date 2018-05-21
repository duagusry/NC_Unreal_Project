#pragma once

#include "GameData.h"

//����, �̺�Ʈ ������ ���� ����ġ ������
struct VariationData
{
	int32 FoodConsumption = 1;
	int32 HealByFood = 8;
	int32 DamageByFood = 24;

	//������ GainData�� LostData�� �����ϴ°͵� ��������..

	//GainData(+��ġ) : �� ȹ�淮, �ķ� ȹ�淮, ȸ����,, ...
	//LostData(-��ġ) : �� �սǷ�, �ķ� �ս�(�Һ�)��, ������, ...
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