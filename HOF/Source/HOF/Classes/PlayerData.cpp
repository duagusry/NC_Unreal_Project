
#include "PlayerData.h"

PlayerData* PlayerData::PlayerDataInstance = nullptr;

void PlayerData::EatFood()
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

void PlayerData::Heal(int32 heal)
{
	int32 TempHealth = CurrentHealth;

	CurrentHealth += heal;
	if (CurrentHealth > MaxHealth)
		CurrentHealth = MaxHealth;
	UE_LOG(LogClass, Warning, TEXT("Healed, %d -> %d / %d(max)"), TempHealth, CurrentHealth, MaxHealth);
}

void PlayerData::GetDamage(int damage)
{
	int32 TempHealth = CurrentHealth;

	CurrentHealth -= damage;
	if (CurrentHealth <= 0)
		CurrentHealth = 0;
	UE_LOG(LogClass, Warning, TEXT("GetDamage, %d -> %d / %d(max)"), TempHealth, CurrentHealth, MaxHealth);

	if (CurrentHealth <= 0)
		Die();
}

void PlayerData::Die()
{
	Alive = false;
	UE_LOG(LogClass, Warning, TEXT("YOU DIED"));
}

PlayerData::PlayerData()
{
	Food = 10;
	Gold = 30;
	MaxHealth = 100;
	CurrentHealth = 100;
	Alive = true;

	//Health ���õ� �κ��� lock �ʿ��ҵ�. (������Ȳ)
}
