// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFGameInstance.h"

UHOFGameInstance::UHOFGameInstance()
{
	//�÷��̾� ������ ���� ����, �ʱ�ȭ
	PlayerData = MakeUnique<FPlayerData>();
}

void UHOFGameInstance::Init()
{
	Super::Init();

	GamePlayState = EGameplayState::Init;
}
