#pragma once

#include "GameFramework/Actor.h"
#include "GameData.h"
#include "HOFWorldCardActor.h"
#include "WorldBoardActor.generated.h"

using namespace SizeInGame;

UCLASS()
class AHOFWorldBoardActor : public AActor
{
	GENERATED_BODY()

public : 
	AHOFWorldBoardActor();
	~AHOFWorldBoardActor();

	void InitWorldStatus();

	// 최초 월드 구성할 때
	void CreateCardAt(int id, int xi, int yi, int32& cardIndex);

	// WorldStatusData가 있을 때
	void CreateCardAt(int xi, int yi, int32& cardIndex, const TArray<BaseStructs::WorldStatusData::WorldSlotDataStruct>& worldStatusDataArray);

	AHOFWorldCardActor& GetCardOn(int x, int y);

	FVector GetCardLocationOn(int x, int y);

	void ResetWorldSlot();

	void InitAdjacentList();
	
	void UpdateAdjacentList(int32 old_x, int32 old_y, int32 new_x, int32 new_y);

	void InitMapInfo();

	void Reveal(int32 amount);

	TArray<BaseStructs::WorldStatusData::WorldSlotDataStruct> SerializeWorldSlotData();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AHOFWorldCardActor> BP_WorldCardActor;

	AHOFWorldCardActor* m_WorldSlot[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT];

	//분명히 인접 리스트를 관리하는 우아한 방법이 있을 것 같은데 모르겠음
	TArray<AHOFWorldCardActor*> m_AdjacentList[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT];

	int32 m_MapEventInfo[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT];
	TArray<int32> m_InitialEventArray;
	TArray<AHOFWorldCardActor*> m_RandomizedCardArray;
};