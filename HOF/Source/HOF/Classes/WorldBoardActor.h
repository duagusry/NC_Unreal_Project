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

	void CreateCardAt(int id, int xi, int yi);

	AHOFWorldCardActor& GetCardOn(int x, int y);

	FVector GetCardLocationOn(int x, int y);

	void ResetWorldSlot();

	void InitAdjacentList();
	
	void UpdateAdjacentList(int32 old_x, int32 old_y, int32 new_x, int32 new_y);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AHOFWorldCardActor> BP_WorldCardActor;

private : 
	AHOFWorldCardActor* m_WorldSlot[WORLD_SLOT_WIDTH][WORLD_SLOT_WIDTH];

	//�и��� ���� ����Ʈ�� �����ϴ� ����� ����� ���� �� ������ �𸣰���
	TArray<AHOFWorldCardActor*> m_AdjacentList[WORLD_SLOT_WIDTH][WORLD_SLOT_WIDTH];
};