
#include "WorldBoardActor.h"
#include "Engine/World.h"
#include "HOFWorldCardActor.h"
#include "HOFCardEvent.h"
#include "ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"

AHOFWorldBoardActor::AHOFWorldBoardActor()
{
	BP_WorldCardActor = nullptr;

	static ConstructorHelpers::FObjectFinder<UBlueprint> WorldCardActorBluePrint(TEXT("Blueprint'/Game/Blueprints/BP_WorldCard'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MapInfoAsset(TEXT("DataTable'/Game/Resource/map'"));

	if (WorldCardActorBluePrint.Object)
	{
		BP_WorldCardActor = CastChecked<UClass>(WorldCardActorBluePrint.Object->GeneratedClass);
	}

	if (MapInfoAsset.Object)
	{
		m_MapInfoTable = MapInfoAsset.Object;
	}

	InitMapInfo();
}

AHOFWorldBoardActor::~AHOFWorldBoardActor()
{
	//게임이 플레이됐다가 종료될 때 한번, 에디터 꺼질 때 한번..
	ResetWorldSlot();
}

void AHOFWorldBoardActor::CreateCardAt(int id, int xi, int yi)
{
	//-1은 공백. 이 숫자도 따로 enum으로 정의를 하던가 해야할 듯.
	if (id == -1)
		return;

	if (id == 0)
		id = m_EventArray[0];

	m_EventArray.Remove(id);
	
	//숫자 안맞으면 크래시 날 듯.

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
			if (i - 1 >= 0 && m_WorldSlot[i - 1][j])
				m_AdjacentList[i][j].Add(m_WorldSlot[i - 1][j]);
			if (i + 1 < WORLD_SLOT_WIDTH && m_WorldSlot[i + 1][j])
				m_AdjacentList[i][j].Add(m_WorldSlot[i + 1][j]);
			if (j - 1 >= 0 && m_WorldSlot[i][j - 1])
				m_AdjacentList[i][j].Add(m_WorldSlot[i][j - 1]);
			if (j + 1 < WORLD_SLOT_HEIGHT && m_WorldSlot[i][j + 1])
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

FMapInfo AHOFWorldBoardActor::GetMapInfoTable(UDataTable * dataTable, FName pName)
{
	m_MapEventInfo;
	return FMapInfo();
}

void AHOFWorldBoardActor::InitMapInfo()
{
	g_CardEvent->AssignEventArray(m_EventArray);
	int32 size = m_EventArray.Num();

	for (int32 i = size - 1; i > 0; i--) {
		int32 j = (FMath::Rand() * (i + 1)) % size;
		int32 temp = m_EventArray[i];
		m_EventArray[i] = m_EventArray[j];
		m_EventArray[j] = temp;
	}
}
