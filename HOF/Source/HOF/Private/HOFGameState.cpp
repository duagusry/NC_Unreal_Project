// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFGameState.h"
#include "Engine/World.h"
#include "HOFWorldGameMode.h"

AHOFGameState::AHOFGameState()
{
	CurrentGameState = EHOFGameState::GAME_INIT;
}

void AHOFGameState::GameStart()
{
	// 뭔가 다른걸 여기서 넣을 수 있을 듯.
	SetState(EHOFGameState::GAME_WORLD);
}

void AHOFGameState::OnGameStart()
{

}

void AHOFGameState::OnDialogEvent()
{

}

void AHOFGameState::OnBattleEvent()
{

}

void AHOFGameState::OnPlayerDead()
{
	// 여기를 어떻게 해야되는데..
	//Cast<AHOFWorldGameMode>(GetWorld()->GetAuthGameMode())->RestartGame();
}

void AHOFGameState::SetState(EHOFGameState newState)
{
	CurrentGameState = newState;

	switch (CurrentGameState)
	{
	case GAME_WORLD :
		OnGameStart();
		break;
	case GAME_DIALOG:
		OnDialogEvent();
		break;
	case GAME_BATTLE : 
		OnBattleEvent();
		break;
	case GAME_DEAD :
		OnPlayerDead();
		break;

	default : 
		break;
	}
}
