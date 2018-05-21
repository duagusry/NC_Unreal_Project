// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFWorldGameMode.h"
#include "Engine/World.h"
#include "HOFWorldPlayerController.h"
#include "HOFSpectatorPawn.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "HOFWorldCardActor.h"
#include "Paths.h"
#include "WorldBoardActor.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

#include "HOFCardEvent.h"

AHOFWorldGameMode::AHOFWorldGameMode()
{
	UE_LOG(LogClass, Warning, TEXT("WorldGameMode Start"));
	PlayerControllerClass = AHOFWorldPlayerController::StaticClass();
	SpectatorClass = AHOFSpectatorPawn::StaticClass();
	DefaultPawnClass = AHOFSpectatorPawn::StaticClass();
	
	BP_WorldPawn = nullptr;

	static ConstructorHelpers::FObjectFinder<UBlueprint> WorldPawnBluePrint(TEXT("Blueprint'/Game/Blueprints/BP_WorldPawn'"));

	if (WorldPawnBluePrint.Object)
	{
		BP_WorldPawn = CastChecked<UClass>(WorldPawnBluePrint.Object->GeneratedClass);
	}
}

void AHOFWorldGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UHOFGameInstance>(GetGameInstance());

	Counter = 3;
	GetWorldTimerManager().SetTimer(countDownHandle, this, &AHOFWorldGameMode::OnTimerTick, 1.0f, true);
	
	GameInstance->SetGamePlayState(EGameplayState::World);

	//���ҽ� �ε�
	g_CardEvent->Parse(FPaths::ProjectDir() + L"Resource/CardEvent.xml");
	
	FActorSpawnParameters SpawnInfo;
	FRotator myRot(0.0f, 0.0f, 0.0f);
	FVector myLoc(0.0f, 0.0f, 0.0f);

	WorldBoard = GetWorld()->SpawnActor<AHOFWorldBoardActor>(AHOFWorldBoardActor::StaticClass(), myLoc, myRot, SpawnInfo);
	for (int i = 0; i < WORLD_SLOT_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_SLOT_HEIGHT; j++)
		{
			WorldBoard->CreateCardAt(1, i, j);
		}
	}
	WorldBoard->InitAdjacentList();
	
	FVector PawnInitialLocaiton = WorldBoard->GetCardLocationOn(0, 0);

	WorldPawn = GetWorld()->SpawnActor<AHOFWorldPawn>(BP_WorldPawn, PawnInitialLocaiton, myRot, SpawnInfo);
	WorldPawn->SetPosition(0, 0);
	WorldBoard->UpdateAdjacentList(0, 0, 0, 0);

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
		g_PlayerData->EatFood();

		UE_LOG(LogClass, Warning, TEXT("Alive? %s"), g_PlayerData->IsAlive() ? TEXT("Alive") : TEXT("Dead"));
		UE_LOG(LogClass, Warning, TEXT("Count %d"), Counter);
		GetWorld()->ServerTravel(FString("/Game/Maps/HOFBattleLevel"));
		GetWorldTimerManager().ClearTimer(countDownHandle);
	}
}

void AHOFWorldGameMode::MovePawnTo(int32 x, int32 y)
{
	BaseStructs::Position oldPosition = g_PlayerData->GetWorldPawnPosition();
	WorldBoard->UpdateAdjacentList(oldPosition.x, oldPosition.y, x, y);

	WorldPawn->SetPosition(x, y);
	WorldPawn->SetLocation(WorldBoard->GetCardLocationOn(x, y));
}


