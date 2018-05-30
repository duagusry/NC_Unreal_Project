// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFPlayerState.h"


AHOFPlayerState::AHOFPlayerState()
{
	CurrentHP = MaxHP = 100.0f;
	CurrentStatePawn = EHOFCharacterState::PEACE;
}

void AHOFPlayerState::SetState(EHOFCharacterState newState)
{
	if (newState == EHOFCharacterState::BATTLE)
		bIsBattleInAction = true;
	else
		bIsBattleInAction = false;

	CurrentStatePawn = newState;
}


