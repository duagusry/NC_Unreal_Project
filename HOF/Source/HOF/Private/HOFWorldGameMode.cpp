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
	GetGameState<AHOFGameState>()->SetState(EHOFGameState::GAME_WORLD);

	//리소스 로딩
	g_CardEvent->Parse(FPaths::ProjectDir() + L"Resource/CardEvent.xml");
	
	//맵 이벤트는 일단 하드코딩. 이후 설정으로 빼서 파싱할 예정..
	int32 MapEventInfo[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT] = \
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

	if (!GameInstance->HasWorldStatusData())
		InitWorld(MapEventInfo);
	else
		LoadWorld(MapEventInfo);

}

void AHOFWorldGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHOFWorldGameMode::InitGameState()
{
	Super::InitGameState();
	auto GameState = GetGameState<AHOFGameState>();
	if (GameState)
	{
		GameState->GameStart();
	}
}

void AHOFWorldGameMode::InitWorld(int32 MapEventInfo[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT])
{
	FActorSpawnParameters SpawnInfo;
	FRotator MyRot(0.0f, 0.0f, 0.0f);
	FVector MyLoc(0.0f, 0.0f, 0.0f);
	int32 CardIndex = 0;

	WorldBoard = GetWorld()->SpawnActor<AHOFWorldBoardActor>(AHOFWorldBoardActor::StaticClass(), MyLoc, MyRot, SpawnInfo);
	WorldBoard->InitMapInfo();
	for (int i = 0; i < WORLD_SLOT_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_SLOT_HEIGHT; j++)
		{
			WorldBoard->CreateCardAt(MapEventInfo[i][j], i, j, CardIndex);
		}
	}

	SpawnPawnOnBoard(0, 0);
	InitWorldBoardPosition(0, 0);
	WorldBoard->GetCardOn(0, 0).Visit();
}

void AHOFWorldGameMode::LoadWorld(int32 MapEventInfo[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT])
{
	FActorSpawnParameters SpawnInfo;
	FRotator MyRot(0.0f, 0.0f, 0.0f);
	FVector MyLoc(0.0f, 0.0f, 0.0f);
	int32 CardIndex = 0;
	const auto& WorldStatusData = GameInstance->WorldStatusData;

	WorldBoard = GetWorld()->SpawnActor<AHOFWorldBoardActor>(AHOFWorldBoardActor::StaticClass(), MyLoc, MyRot, SpawnInfo);
	WorldBoard->m_InitialEventArray = WorldStatusData.WorldBoardData.InitialEventArray;
	for (int i = 0; i < WORLD_SLOT_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_SLOT_HEIGHT; j++)
		{
			if(MapEventInfo[i][j] != -1)
				WorldBoard->CreateCardAt(i, j, CardIndex, WorldStatusData.WorldBoardData.WorldSlotData);
		}
	}

	BaseStructs::Position LastPosition = WorldStatusData.CurrentPosition;
	SpawnPawnOnBoard(LastPosition.x, LastPosition.y);
	InitWorldBoardPosition(LastPosition.x, LastPosition.y);
	WorldBoard->GetCardOn(LastPosition.x, LastPosition.y).Visit(WorldStatusData.CurrentDialogId);
}

void AHOFWorldGameMode::MovePawnTo(int32 x, int32 y)
{
	BaseStructs::Position OldPosition = WorldPawn->GetPosition();
	WorldBoard->UpdateAdjacentList(OldPosition.x, OldPosition.y, x, y);

	FVector TargetCardLocation = WorldBoard->GetCardLocationOn(x, y);

	WorldPawn->SetPosition(x, y);
	WorldPawn->SetRotation(TargetCardLocation);
	WorldPawn->SetLocation(TargetCardLocation);
}

void AHOFWorldGameMode::HandleRevealEvent(int32 Amount)
{
	WorldBoard->Reveal(Amount);
}

void AHOFWorldGameMode::SpawnPawnOnBoard(int32 x, int32 y)
{
	FActorSpawnParameters SpawnInfo;
	FRotator MyRot(0.0f, 0.0f, 0.0f);
	FVector PawnInitialLocaiton = WorldBoard->GetCardLocationOn(x, y);

	WorldPawn = GetWorld()->SpawnActor<AHOFWorldPawn>(BP_WorldPawn, PawnInitialLocaiton, MyRot, SpawnInfo);
	WorldPawn->SetPosition(x, y);
}

void AHOFWorldGameMode::InitWorldBoardPosition(int32 x, int32 y)
{
	WorldBoard->InitWorldStatus();
	WorldBoard->InitAdjacentList();
	WorldBoard->UpdateAdjacentList(0, 0, x, y);
}

BaseStructs::WorldStatusData AHOFWorldGameMode::AssignWorldStatusData(int32 returnDialogId)
{
	return BaseStructs::WorldStatusData
		{ BaseStructs::WorldStatusData::WorldBoardDataStruct
			{ WorldBoard->SerializeWorldSlotData(), 
			WorldBoard->m_InitialEventArray 
			}, 
			WorldPawn->GetPosition(), 
			returnDialogId
		};
}


