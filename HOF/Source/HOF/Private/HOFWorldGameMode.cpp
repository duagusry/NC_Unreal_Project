// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFWorldGameMode.h"
#include "Engine/World.h"
#include "HOFWorldPlayerController.h"
#include "HOFSpectatorPawn.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "HOFWorldCardActor.h"
#include "Paths.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

#include "HOFCardEvent.h"

AHOFWorldGameMode::AHOFWorldGameMode()
{
	UE_LOG(LogClass, Warning, TEXT("WorldGameMode Start"));
	PlayerControllerClass = AHOFWorldPlayerController::StaticClass();
	SpectatorClass = AHOFSpectatorPawn::StaticClass();
	DefaultPawnClass = AHOFSpectatorPawn::StaticClass();
}

void AHOFWorldGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UHOFGameInstance>(GetGameInstance());

	Counter = 3;
	GetWorldTimerManager().SetTimer(countDownHandle, this, &AHOFWorldGameMode::OnTimerTick, 1.0f, true);

	//PlayerData ��������
	PlayerData = GameInstance->GetPlayerData();

	GameInstance->SetGamePlayState(EGameplayState::World);

	//���ҽ� �ε�
	g_CardEvent->Parse(FPaths::GameDir() + L"Resource/CardEvent.xml");
	
	//�׽�Ʈ�� ����.
	//���������� Ȯ�� ���غð� ������ ����ִ����� Ȯ��.
	FActorSpawnParameters SpawnInfo;
	FRotator myRot(0.0f, 0.0f, 0.0f);
	FVector myLoc(0.0f, 0.0f, 100.0f);
	
	AHOFWorldCardActor* a = GetWorld()->SpawnActor<AHOFWorldCardActor>(AHOFWorldCardActor::StaticClass(), myLoc, myRot, SpawnInfo);
	a->Init(1, 2, 3);
	
}

void AHOFWorldGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHOFWorldGameMode::InitGameState()
{
	Super::InitGameState();
}

void AHOFWorldGameMode::OnTimerTick()
{
	//--Counter;

	//Ÿ�̸� ����� BattleLevel ����
	if (Counter < 1)
	{
		PlayerData->EatFood();

		UE_LOG(LogClass, Warning, TEXT("Alive? %s"), PlayerData->IsAlive() ? TEXT("Alive") : TEXT("Dead"));
		UE_LOG(LogClass, Warning, TEXT("Count %d"), Counter);
		GameInstance->SetPlayerData(PlayerData);
		GetWorld()->ServerTravel(FString("/Game/Maps/HOFBattleLevel"));
		GetWorldTimerManager().ClearTimer(countDownHandle);
	}
}


