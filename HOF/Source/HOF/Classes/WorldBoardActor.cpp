
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
		AHOFWorldCardActor* newCard = world->SpawnActor<AHOFWorldCardActor>(BP_WorldCardActor, myLoc, myRot, SpawnInfo);
		newCard->Init(id, xi, yi);
		m_WorldSlot[xi][yi] = newCard;
	}
}

AHOFWorldCardActor & AHOFWorldBoardActor::GetCardOn(int x, int y)
{
	return *m_WorldSlot[x][y];
}

void AHOFWorldBoardActor::ResetWorldSlot()
{
	for (int i = 0; i < WORLD_SLOT_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_SLOT_HEIGHT; j++)
		{
			m_WorldSlot[i][j]->Destroy();
		}
	}
}
