// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFWorldGameMode.h"
#include "Engine/World.h"
#include "HOFWorldPlayerController.h"
#include "HOFSpectatorPawn.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

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

	//PlayerData 이전받음
	PlayerData = GameInstance->GetPlayerData();

	GameInstance->SetGamePlayState(EGameplayState::World);
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

	//타이머 만료시 BattleLevel 오픈
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


