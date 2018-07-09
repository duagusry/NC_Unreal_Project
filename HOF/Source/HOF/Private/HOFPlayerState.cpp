// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFPlayerState.h"
#include "Engine/World.h"
#include "HOFWorldPlayerController.h"
#include "HOFWorldGameMode.h"
#include "HOFGameState.h"

AHOFPlayerState::AHOFPlayerState()
{
	CurrentHP = MaxHP = 100.0f;
	CurrentStatePawn = EHOFCharacterState::PLAYER_PEACE;
	Food = 0;
	Gold = 30;
	Alive = true;
}

void AHOFPlayerState::SetState(EHOFCharacterState newState)
{
	if (newState == EHOFCharacterState::PLAYER_BATTLE)
		bIsBattleInAction = true;
	else
		bIsBattleInAction = false;

	CurrentStatePawn = newState;
}

EHOFCharacterState AHOFPlayerState::GetState()
{
	return CurrentStatePawn;
}

void AHOFPlayerState::EatFood()
{
	//식량이 모자라면 데미지를 받음
	if (Food < NumberInGame::FoodConsumption)
	{
		Food = 0;
		GetDamage(NumberInGame::DamageByFood);

		return;
	}

	Food -= NumberInGame::FoodConsumption;
	UE_LOG(LogClass, Warning, TEXT("Food Consumed, Current Food : %d"), Food);

	Heal(NumberInGame::HealByFood);
}

void AHOFPlayerState::Heal(int32 heal)
{
	int32 TempHP = CurrentHP;

	CurrentHP += heal;
	if (CurrentHP > MaxHP)
		CurrentHP = MaxHP;
	UE_LOG(LogClass, Warning, TEXT("Healed, %d -> %d / %d(max)"), TempHP, CurrentHP, MaxHP);
}

void AHOFPlayerState::GetDamage(int damage)
{
	int32 TempHP = CurrentHP;

	CurrentHP -= damage;
	if (CurrentHP <= 0)
		CurrentHP = 0;
	UE_LOG(LogClass, Warning, TEXT("GetDamage, %d -> %d / %d(max)"), TempHP, CurrentHP, MaxHP);

	if (CurrentHP <= 0)
		Die();
}

void AHOFPlayerState::Die()
{
	Alive = false;
	UE_LOG(LogClass, Warning, TEXT("YOU DIED"));
	CurrentStatePawn = EHOFCharacterState::PLAYER_DEAD;

	auto GameMode = Cast<AHOFWorldGameMode>(GetWorld()->GetAuthGameMode());
	Cast<AHOFGameState>(GameMode->GameState)->SetState(EHOFGameState::GAME_DEAD);
}


