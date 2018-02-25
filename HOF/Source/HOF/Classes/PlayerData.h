#pragma once

#include "PlayerData.generated.h"

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

		//Health ���õ� �κ��� lock �ʿ��ҵ�. (������Ȳ)
	}

	void EatFood()
	{
		//�ķ��� ���ڶ�� �������� ����
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