// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HOFInputInterface.h"
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
	void BattleEvent(/* TMap<int, int>& spawnList, int mapNumber */);

private : 
	int32 x;
	int32 y;
	//이벤트를 어떻게 할까
	//별도의 CardEvent 클래스 혹은 protobuf 메시지로 정의해놓고 리소스에서 그 데이터 구성해서 들고 있도록.
	
};
