// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFPlayerState.h"


void AHOFPlayerState::SetState(HOFCharacterState newState)
{
	if (newState == HOFCharacterState::BATTLE)
		bIsBattleInAction = true;
	else
		bIsBattleInAction = false;

	CurrentStatePawn = newState;
}


