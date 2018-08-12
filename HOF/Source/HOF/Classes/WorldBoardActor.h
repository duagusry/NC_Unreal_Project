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

	// ���� ���� ������ ��
	void CreateCardAt(int id, int xi, int yi, int32& cardIndex);

	// WorldStatusData�� ���� ��
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

	//�и��� ���� ����Ʈ�� �����ϴ� ����� ����� ���� �� ������ �𸣰���
	TArray<AHOFWorldCardActor*> m_AdjacentList[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT];

	int32 m_MapEventInfo[WORLD_SLOT_WIDTH][WORLD_SLOT_HEIGHT];
	TArray<int32> m_InitialEventArray;
	TArray<AHOFWorldCardActor*> m_RandomizedCardArray;
};