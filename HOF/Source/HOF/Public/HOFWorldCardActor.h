// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HOFInputInterface.h"
#include "GameFramework/Actor.h"
#include "GameData.h"
#include "HOFCardEvent.h"
#include "HOFWorldCardActor.generated.h"

UCLASS()
class HOF_API AHOFWorldCardActor : public AActor, 
	public IHOFInputInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHOFWorldCardActor();

	void Init(int32 id, int32 x, int32 y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//IHOFInterface
	virtual void OnInputTap_Implementation() override;

	//Battle Mode로 전환
	/*
		Params
		map<int monsterId, int monsterCount>& SpawnList : 전환된 맵에서 소환될 몬스터 리스트(추후에는 별도 오브젝트로 구현하는게 좋을 듯.)
		int mapNumber : 배경 맵 번호(몇개의 프리셋을 만들어놓고 재활용?)
		etc... : 추가적으로 이벤트성의 설정이 들어갈 수 있을 듯. ex.) 시간제한, 보스전 여부, 기타 이벤트

	*/
	void TextEvent(int32 returnDialog = 1);
	
	void SetAdjacency(bool isAdjacent);

	void Reveal();

	void Visit(int32 returnDialog = 1);

	inline bool IsRevealed() { return Revealed; }

	void SetCardDataFromWorldStatusData(const BaseStructs::WorldStatusData::WorldSlotDataStruct&worldStatusrData);

public : 
	//WorldPawn과 인접해있는지 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Default)
	bool IsAdjacentToPawn;

	//WorldBoardActor상의 좌표
	int32 X;
	int32 Y;
	bool Revealed;
	bool IsVisited;
	
	FText Title;
	HOFCardEvent CardEvent;
};
