
#include "WorldBoardActor.h"
#include "Engine/World.h"
#include "HOFWorldCardActor.h"
#include "ConstructorHelpers.h"

AHOFWorldBoardActor::AHOFWorldBoardActor()
{
	BP_WorldCardActor = nullptr;

	static ConstructorHelpers::FObjectFinder<UBlueprint> WorldCardActorBluePrint(TEXT("Blueprint'/Game/Blueprints/BP_WorldCard'"));

	if (WorldCardActorBluePrint.Object)
	{
		BP_WorldCardActor = CastChecked<UClass>(WorldCardActorBluePrint.Object->GeneratedClass);
	}
}

AHOFWorldBoardActor::~AHOFWorldBoardActor()
{
	//게임이 플레이됐다가 종료될 때 한번, 에디터 꺼질 때 한번..
	ResetWorldSlot();
}

void AHOFWorldBoardActor::CreateCardAt(int id, int xi, int yi)
{
	float realSlotSizeY = WORLD_WIDTH / WORLD_SLOT_WIDTH;
	float realSlotSizeX = WORLD_HEIGHT / WORLD_SLOT_HEIGHT;

	float LocY = BOARD_BASE_LOC_Y - (WORLD_WIDTH / 2) + ((realSlotSizeY / 2) + (realSlotSizeY * xi));
	float LocX = BOARD_BASE_LOC_X + (WORLD_HEIGHT / 2) - ((realSlotSizeX / 2) + (realSlotSizeX * yi));

	FActorSpawnParameters SpawnInfo;
	FRotator myRot(0.0f, 0.0f, 0.0f);
	FVector myLoc(LocX, LocY, 20.0f);
	
	UWorld* world = GetWorld();
	if (world && BP_WorldCardActor)
	{
		AHOFWorldCardActor* newCard(world->SpawnActor<AHOFWorldCardActor>(BP_WorldCardActor, myLoc, myRot, SpawnInfo));
		newCard->Init(id, xi, yi);
		m_WorldSlot[xi][yi] = newCard;
	}
}

AHOFWorldCardActor & AHOFWorldBoardActor::GetCardOn(int x, int y)
{
	return *m_WorldSlot[x][y];
}

FVector AHOFWorldBoardActor::GetCardLocationOn(int x, int y)
{
	return m_WorldSlot[x][y]->GetActorLocation();
}

void AHOFWorldBoardActor::ResetWorldSlot()
{
	//TSharedPtr로 변경 고려해야 할 듯..

	for (int i = 0; i < WORLD_SLOT_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_SLOT_HEIGHT; j++)
		{
			if (m_WorldSlot[i][j])
				m_WorldSlot[i][j]->Destroy();

			if (m_AdjacentList[i][j].Num())
				m_AdjacentList[i][j].Empty();
		}
	}
}

void AHOFWorldBoardActor::InitAdjacentList()
{
	//The Love..
	for (int i = 0; i < WORLD_SLOT_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_SLOT_HEIGHT; j++)
		{
			if (i - 1 >= 0)
				m_AdjacentList[i][j].Add(m_WorldSlot[i - 1][j]);
			if (i + 1 < WORLD_SLOT_WIDTH)
				m_AdjacentList[i][j].Add(m_WorldSlot[i + 1][j]);
			if (j - 1 >= 0)
				m_AdjacentList[i][j].Add(m_WorldSlot[i][j - 1]);
			if (j + 1 < WORLD_SLOT_HEIGHT)
				m_AdjacentList[i][j].Add(m_WorldSlot[i][j + 1]);
		}
	}
}

void AHOFWorldBoardActor::UpdateAdjacentList(int32 old_x, int32 old_y, int32 new_x, int32 new_y)
{
	for (auto card : m_AdjacentList[old_x][old_y])
	{
		card->SetAdjacency(false);
	}

	for (auto card : m_AdjacentList[new_x][new_y])
	{
		card->SetAdjacency(true);
	}
}
