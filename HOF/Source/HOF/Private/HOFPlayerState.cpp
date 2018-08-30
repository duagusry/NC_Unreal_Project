// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFPlayerState.h"
#include "Engine/World.h"
#include "HOFWorldPlayerController.h"
#include "HOFWorldGameMode.h"
#include "HOFGameState.h"
#include "GameData.h"

AHOFPlayerState::AHOFPlayerState()
{
	CurrentStatePawn = EHOFCharacterState::PLAYER_PEACE;
}

void AHOFPlayerState::SetPlayerData(BaseStructs::PlayerData playerData)
{
	PlayerData.HP = playerData.HP;
	PlayerData.Food = playerData.Food;
	PlayerData.Gold = playerData.Gold;
	PlayerData.Alive = playerData.Alive;
}

void AHOFPlayerState::SetState(EHOFCharacterState newState)
{
	if (newState == EHOFCharacterState::PLAYER_BATTLE)
		bIsBattleInAction = true;
	else
		bIsBattleInAction = false;

	CurrentStatePawn = newState;
}

void AHOFPlayerState::EatFood()
{
	//식량이 모자라면 데미지를 받음
	PlayerData.Food(-NumberInGame::FoodConsumption);

	if (PlayerData.Food.CheckOnMinValue())
	{
		GetDamage(NumberInGame::DamageByFood);

		return;
	}

	UE_LOG(LogClass, Warning, TEXT("Food Consumed, Current Food : %d"), PlayerData.Food.GetCurrentValue());

	Heal(NumberInGame::HealByFood);
}

void AHOFPlayerState::Heal(int32 heal)
{
	float TempHP = PlayerData.HP.GetCurrentValue();

	PlayerData.HP(heal);

	UE_LOG(LogClass, Warning, TEXT("Healed, %f -> %f / %f(max)"), TempHP, PlayerData.HP.GetCurrentValue(), PlayerData.HP.GetMaxValue());
}

void AHOFPlayerState::GetDamage(int damage)
{
	float TempHP = PlayerData.HP.GetCurrentValue();

	PlayerData.HP(-damage);
	UE_LOG(LogClass, Warning, TEXT("GetDamage, %f -> %f / %f(max)"), TempHP, PlayerData.HP.GetCurrentValue(), PlayerData.HP.GetMaxValue());

	if (PlayerData.HP.CheckOnMinValue())
		Die();
}

void AHOFPlayerState::Die()
{
	PlayerData.Alive = false;
	UE_LOG(LogClass, Warning, TEXT("YOU DIED"));
	CurrentStatePawn = EHOFCharacterState::PLAYER_DEAD;

	auto GameMode = Cast<AHOFWorldGameMode>(GetWorld()->GetAuthGameMode());
	Cast<AHOFGameState>(GameMode->GameState)->SetState(EHOFGameState::GAME_DEAD);
}


