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

	//Battle Mode�� ��ȯ
	/*
		Params
		map<int monsterId, int monsterCount>& SpawnList : ��ȯ�� �ʿ��� ��ȯ�� ���� ����Ʈ(���Ŀ��� ���� ������Ʈ�� �����ϴ°� ���� ��.)
		int mapNumber : ��� �� ��ȣ(��� �������� �������� ��Ȱ��?)
		etc... : �߰������� �̺�Ʈ���� ������ �� �� ���� ��. ex.) �ð�����, ������ ����, ��Ÿ �̺�Ʈ

	*/
	void TextEvent(int32 returnDialog = 1);
	
	void SetAdjacency(bool isAdjacent);

	void Reveal();

	void Visit(int32 returnDialog = 1);

	inline bool IsRevealed() { return Revealed; }

	void SetCardDataFromWorldStatusData(const BaseStructs::WorldStatusData::WorldSlotDataStruct&worldStatusrData);

public : 
	//WorldPawn�� �������ִ��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Default)
	bool IsAdjacentToPawn;

	//WorldBoardActor���� ��ǥ
	int32 X;
	int32 Y;
	bool Revealed;
	bool IsVisited;
	
	FText Title;
	HOFCardEvent CardEvent;
};
