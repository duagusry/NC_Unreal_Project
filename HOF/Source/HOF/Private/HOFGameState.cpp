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
	// ���� �ٸ��� ���⼭ ���� �� ���� ��.
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
	// ���⸦ ��� �ؾߵǴµ�..
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
