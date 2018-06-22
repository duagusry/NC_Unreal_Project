#pragma once

#include "GameFramework/Actor.h"
#include "GameData.h"
#include "HOFWorldCardActor.h"
#include "MapData.h"
#include "WorldBoardActor.generated.h"

using namespace SizeInGame;

UCLASS()
class AHOFWorldBoardActor : public AActor
{
	GENERATED_BODY()

public : 
	AHOFWorldBoardActor();
	~AHOFWorldBoardActor();

	void CreateCardAt(int id, int xi, int yi);

	AHOFWorldCardActor& GetCardOn(int x, int y);

	FVector GetCardLocationOn(int x, int y);

	void ResetWorldSlot();

	void InitAdjacentList();
	
	void UpdateAdjacentList(int32 old_x, int32 old_y, int32 new_x, int32 new_y);

	FMapInfo GetMapInfoTable(UDataTable* dataTable, FName pName);
	
	void InitMapInfo();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AHOFWorldCardActor> BP_WorldCardActor;

private : 
	AHOFWorldCardActor* m_WorldSlot[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT];

	//분명히 인접 리스트를 관리하는 우아한 방법이 있을 것 같은데 모르겠음
	TArray<AHOFWorldCardActor*> m_AdjacentList[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT];

	UDataTable* m_MapInfoTable;
	int32 m_MapEventInfo[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT];
	TArray<int32> m_EventArray;
};