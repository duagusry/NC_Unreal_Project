// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HOFInputInterface.h"
#include "HOFCardEvent.h"
#include "GameFramework/Actor.h"
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
	void BattleEvent(/* TMap<int, int>& spawnList, int mapNumber */);

private : 
	//WorldBoardActor���� ��ǥ
	int32 m_X;
	int32 m_Y;

	HOFCardEvent m_CardEvent;
};