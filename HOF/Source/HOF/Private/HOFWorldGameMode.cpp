// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFWorldGameMode.h"
#include "Engine/World.h"
#include "HOFWorldPlayerController.h"
#include "HOFSpectatorPawn.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "HOFWorldCardActor.h"
#include "Paths.h"
#include "WorldBoardActor.h"
#include "HOFGameState.h"
#include "HOFPlayerState.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

#include "HOFCardEvent.h"

AHOFWorldGameMode::AHOFWorldGameMode()
{
	UE_LOG(LogClass, Warning, TEXT("WorldGameMode Start"));
	PlayerControllerClass = AHOFWorldPlayerController::StaticClass();
	SpectatorClass = AHOFSpectatorPawn::StaticClass();
	DefaultPawnClass = AHOFSpectatorPawn::StaticClass();
	GameStateClass = AHOFGameState::StaticClass();
	PlayerStateClass = AHOFPlayerState::StaticClass();

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
	
	GameInstance->SetGamePlayState(EGameplayState::World);		// 이걸 따로 유지할 필요가..?
	GetGameState<AHOFGameState>()->SetState(EHOFGameState::GAME_WORLD);

	//리소스 로딩
	g_CardEvent->Parse(FPaths::ProjectDir() + L"Resource/CardEvent.xml");
	
	//맵 이벤트는 일단 하드코딩. 이후 설정으로 빼서 파싱할 예정..
	int32 mapEventInfo[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT] = \
		/*
	{
		{ 0, 1, 2, 0, -1, -1, -1, 0 },
		{ -1, -1, 0, -1, -1, -1, -1, 0 },
		{ -1, -1, 0, 0, -1, -1, 0, 0 },
		{ 0, -1, 0, 0, 0, 0, 0, -1 },
		{ 0, -1, -1, -1, -1, -1, 0, -1 },
		{ 0, 0, 0, -1, -1, 0, 0, 0 },
		{ 0, -1, -1, -1, 0, 0, -1, -1 },
		{ 0, 0, 0, 0, 0, -1, -1, -1 }
	};
	*/
	{
		{ 1, 2, 0 },
		{ -1, 8, 0 },
		{ 0, 0, 0 }
	};

	if (!GameInstance->HasTransferData())
		InitWorld(mapEventInfo);
	else
		LoadWorld(mapEventInfo);

}

void AHOFWorldGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHOFWorldGameMode::InitGameState()
{
	Super::InitGameState();
	/*
	AHOFGameState* const AHOFGameState = GetGameState<AHOFGameState>();
	if (AHOFGameState)
	{
		AHOFGameState->GameStart();
	}
	*/
}

void AHOFWorldGameMode::InitWorld(int32 mapEventInfo[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT])
{
	FActorSpawnParameters SpawnInfo;
	FRotator myRot(0.0f, 0.0f, 0.0f);
	FVector myLoc(0.0f, 0.0f, 0.0f);
	int32 cardIndex = 0;

	WorldBoard = GetWorld()->SpawnActor<AHOFWorldBoardActor>(AHOFWorldBoardActor::StaticClass(), myLoc, myRot, SpawnInfo);
	WorldBoard->InitMapInfo();
	for (int i = 0; i < WORLD_SLOT_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_SLOT_HEIGHT; j++)
		{
			WorldBoard->CreateCardAt(mapEventInfo[i][j], i, j, cardIndex);
		}
	}

	SpawnPawnOnBoard(0, 0);
	InitWorldBoardPosition(0, 0);
	WorldBoard->GetCardOn(0, 0).Visit();
}

void AHOFWorldGameMode::LoadWorld(int32 mapEventInfo[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT])
{
	FActorSpawnParameters SpawnInfo;
	FRotator myRot(0.0f, 0.0f, 0.0f);
	FVector myLoc(0.0f, 0.0f, 0.0f);
	int32 cardIndex = 0;
	auto transferData = GameInstance->TransferData;

	WorldBoard = GetWorld()->SpawnActor<AHOFWorldBoardActor>(AHOFWorldBoardActor::StaticClass(), myLoc, myRot, SpawnInfo);
	WorldBoard->m_InitialEventArray = transferData.WorldBoardData.InitialEventArray;
	for (int i = 0; i < WORLD_SLOT_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_SLOT_HEIGHT; j++)
		{
			if(mapEventInfo[i][j] != -1)
				WorldBoard->CreateCardAt(i, j, cardIndex, transferData.WorldBoardData.WorldSlotData);
		}
	}

	BaseStructs::Position LastPosition = transferData.CurrentPosition;
	SpawnPawnOnBoard(LastPosition.x, LastPosition.y);
	InitWorldBoardPosition(LastPosition.x, LastPosition.y);
	WorldBoard->GetCardOn(LastPosition.x, LastPosition.y).Visit(transferData.CurrentDialogId);
}

void AHOFWorldGameMode::OnTimerTick()
{
	//--Counter;

	//타이머 만료시 BattleLevel 오픈
	/*
	if (Counter < 1)
	{
		g_PlayerData->EatFood();

		UE_LOG(LogClass, Warning, TEXT("Alive? %s"), g_PlayerData->IsAlive() ? TEXT("Alive") : TEXT("Dead"));
		UE_LOG(LogClass, Warning, TEXT("Count %d"), Counter);
		GetWorld()->ServerTravel(FString("/Game/Maps/HOFBattleLevel"));
		GetWorldTimerManager().ClearTimer(countDownHandle);
	}
	*/
}

void AHOFWorldGameMode::MovePawnTo(int32 x, int32 y)
{
	BaseStructs::Position oldPosition = WorldPawn->GetPosition();
	WorldBoard->UpdateAdjacentList(oldPosition.x, oldPosition.y, x, y);

	FVector targetCardLocation = WorldBoard->GetCardLocationOn(x, y);

	WorldPawn->SetPosition(x, y);
	WorldPawn->SetRotation(targetCardLocation);
	WorldPawn->SetLocation(targetCardLocation);
}

void AHOFWorldGameMode::HandleRevealEvent(int32 amount)
{
	WorldBoard->Reveal(amount);
}

void AHOFWorldGameMode::SpawnPawnOnBoard(int32 x, int32 y)
{
	FActorSpawnParameters SpawnInfo;
	FRotator myRot(0.0f, 0.0f, 0.0f);
	FVector myLoc(0.0f, 0.0f, 0.0f);

	FVector PawnInitialLocaiton = WorldBoard->GetCardLocationOn(x, y);

	WorldPawn = GetWorld()->SpawnActor<AHOFWorldPawn>(BP_WorldPawn, PawnInitialLocaiton, myRot, SpawnInfo);
	WorldPawn->SetPosition(x, y);
}

void AHOFWorldGameMode::InitWorldBoardPosition(int32 x, int32 y)
{
	WorldBoard->InitWorldStatus();
	WorldBoard->InitAdjacentList();
	WorldBoard->UpdateAdjacentList(0, 0, x, y);
}


