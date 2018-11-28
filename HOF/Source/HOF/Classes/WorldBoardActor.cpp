
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

	if (WorldCardActorBluePrint.Object)
	{
		BP_WorldCardActor = CastChecked<UClass>(WorldCardActorBluePrint.Object->GeneratedClass);
	}
}

AHOFWorldBoardActor::~AHOFWorldBoardActor()
{
	//게임이 플레이됐다가 종료될 때 한번, 에디터 꺼질 때 한번..
	//ResetWorldSlot();
}

void AHOFWorldBoardActor::InitWorldStatus()
{
	// RandomizedCardArray 초기화.
	int32 size = RandomizedCardArray.Num();

	for (int32 i = size - 1; i > 0; i--) 
	{
		int32 j = (FMath::Rand() * (i + 1)) % size;
		auto temp = RandomizedCardArray[i];
		RandomizedCardArray[i] = RandomizedCardArray[j];
		RandomizedCardArray[j] = temp;
	}
}

// for init
void AHOFWorldBoardActor::CreateCardAt(int id, int xi, int yi, int32& cardIndex)
{
	//-1은 공백. 이 숫자도 따로 enum으로 정의를 하던가 해야할 듯.
	if (id == -1)
		return;

	// random
	if (id == 0)
		id = InitialEventArray[cardIndex++];

	float LocY = BOARD_BASE_LOC_Y - (WORLD_WIDTH / 2) + ((REAL_SLOT_SIZE_Y / 2) + (REAL_SLOT_SIZE_Y * xi));
	float LocX = BOARD_BASE_LOC_X + (WORLD_HEIGHT / 2) - ((REAL_SLOT_SIZE_X / 2) + (REAL_SLOT_SIZE_X * yi));

	FActorSpawnParameters SpawnInfo;
	FRotator MyRot(0.0f, 0.0f, 0.0f);
	FVector MyLoc(LocX, LocY, 20.0f);
	
	UWorld* World = GetWorld();
	if (World && BP_WorldCardActor)
	{
		AHOFWorldCardActor* NewCard(World->SpawnActor<AHOFWorldCardActor>(BP_WorldCardActor, MyLoc, MyRot, SpawnInfo));
		NewCard->Init(id, xi, yi);
		WorldSlot[xi][yi] = NewCard;

		RandomizedCardArray.Add(NewCard);
	}
}

// for load
void AHOFWorldBoardActor::CreateCardAt(int xi, int yi, int32 & cardIndex, const TArray<BaseStructs::WorldStatusData::WorldSlotDataStruct>& worldStatusDataArray)
{
	const float LocY = BOARD_BASE_LOC_Y - (WORLD_WIDTH / 2) + ((REAL_SLOT_SIZE_Y / 2) + (REAL_SLOT_SIZE_Y * xi));
	const float LocX = BOARD_BASE_LOC_X + (WORLD_HEIGHT / 2) - ((REAL_SLOT_SIZE_X / 2) + (REAL_SLOT_SIZE_X * yi));

	FActorSpawnParameters SpawnInfo;
	FRotator MyRot(0.0f, 0.0f, 0.0f);
	FVector MyLoc(LocX, LocY, 20.0f);

	UWorld* World = GetWorld();
	if (World && BP_WorldCardActor)
	{
		AHOFWorldCardActor* NewCard(World->SpawnActor<AHOFWorldCardActor>(BP_WorldCardActor, MyLoc, MyRot, SpawnInfo));
		NewCard->Init(worldStatusDataArray[cardIndex].EventId, xi, yi);
		NewCard->SetCardDataFromWorldStatusData(worldStatusDataArray[cardIndex]);
		cardIndex++;
		WorldSlot[xi][yi] = NewCard;

		RandomizedCardArray.Add(NewCard);
	}
}

AHOFWorldCardActor & AHOFWorldBoardActor::GetCardOn(int x, int y)
{
	return *WorldSlot[x][y];
}

FVector AHOFWorldBoardActor::GetCardLocationOn(int x, int y)
{
	return WorldSlot[x][y]->GetActorLocation();
}

void AHOFWorldBoardActor::ResetWorldSlot()
{
	//TSharedPtr로 변경 고려해야 할 듯..

	for (int i = 0; i < WORLD_SLOT_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_SLOT_HEIGHT; j++)
		{
			if (WorldSlot[i][j])
				WorldSlot[i][j]->Destroy();

			if (AdjacentList[i][j].Num())
				AdjacentList[i][j].Empty();
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
			if (i - 1 >= 0 && WorldSlot[i - 1][j])
				AdjacentList[i][j].Add(WorldSlot[i - 1][j]);
			if (i + 1 < WORLD_SLOT_WIDTH && WorldSlot[i + 1][j])
				AdjacentList[i][j].Add(WorldSlot[i + 1][j]);
			if (j - 1 >= 0 && WorldSlot[i][j - 1])
				AdjacentList[i][j].Add(WorldSlot[i][j - 1]);
			if (j + 1 < WORLD_SLOT_HEIGHT && WorldSlot[i][j + 1])
				AdjacentList[i][j].Add(WorldSlot[i][j + 1]);
		}
	}
}

void AHOFWorldBoardActor::UpdateAdjacentList(int32 old_x, int32 old_y, int32 new_x, int32 new_y)
{
	for (auto card : AdjacentList[old_x][old_y])
	{
		card->SetAdjacency(false);
	}

	for (auto card : AdjacentList[new_x][new_y])
	{
		card->SetAdjacency(true);
	}
}


void AHOFWorldBoardActor::InitMapInfo(int32 mapEventInfo[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT])
{
	g_CardEvent->AssignEventArray(InitialEventArray);

	// remove fixed id
	for (int i = 0; i < WORLD_SLOT_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_SLOT_HEIGHT; j++)
		{
			if (mapEventInfo[i][j] != 0)
				InitialEventArray.Remove(mapEventInfo[i][j]);
		}
	}

	int32 Size = InitialEventArray.Num();
	for (int32 i = Size - 1; i > 0; i--)
	{
		int32 j = (FMath::Rand() * (i + 1)) % Size;
		int32 temp = InitialEventArray[i];
		InitialEventArray[i] = InitialEventArray[j];
		InitialEventArray[j] = temp;
	}
}

void AHOFWorldBoardActor::Reveal(int32 amount)
{
	int32 Index = 0;
	int32 Size = RandomizedCardArray.Num();
	AHOFWorldCardActor* TargetCard;

	while (amount-- > 0)
	{
		for (Index; Index < Size; Index++)
		{
			TargetCard = RandomizedCardArray[Index];
			if (!TargetCard->IsRevealed())
			{
				TargetCard->Reveal();
				break;
			}
		}
	}
}

TArray<BaseStructs::WorldStatusData::WorldSlotDataStruct> AHOFWorldBoardActor::SerializeWorldSlotData()
{
	TArray<BaseStructs::WorldStatusData::WorldSlotDataStruct> SerializedSlotArray;
	for (int i = 0; i < WORLD_SLOT_WIDTH; i++)
		for (int j = 0; j < WORLD_SLOT_HEIGHT; j++)
		{
			if(WorldSlot[i][j])
				SerializedSlotArray.Add(BaseStructs::WorldStatusData::WorldSlotDataStruct{ WorldSlot[i][j]->CardEvent.GetID() , WorldSlot[i][j]->IsVisited, WorldSlot[i][j]->Revealed });
		}

	return SerializedSlotArray;
}

