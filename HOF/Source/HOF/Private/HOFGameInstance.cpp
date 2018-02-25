// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFGameInstance.h"

UHOFGameInstance::UHOFGameInstance()
{
	//플레이어 데이터 최초 생성, 초기화
	PlayerData = MakeUnique<FPlayerData>();
}

void UHOFGameInstance::Init()
{
	Super::Init();

	GamePlayState = EGameplayState::Init;
}
