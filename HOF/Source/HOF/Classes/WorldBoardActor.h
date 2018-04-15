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

	void CreateCardAt(int id, int xi, int yi);

	AHOFWorldCardActor& GetCardOn(int x, int y);

	void ResetWorldSlot();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AHOFWorldCardActor> BP_WorldCardActor;

private : 
	AHOFWorldCardActor* m_WorldSlot[WORLD_SLOT_WIDTH][WORLD_SLOT_WIDTH];
};