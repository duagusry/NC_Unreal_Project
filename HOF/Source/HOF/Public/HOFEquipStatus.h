// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameData.h"
#include "HOFEquipStatus.generated.h"

class AHOFItem;
class AHOFGearItem;

UCLASS()
class HOF_API AHOFEquipStatus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHOFEquipStatus();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Equip(EHOFItemType slotNumber, AHOFItem* item);
	void Equip(EHOFItemType slotNumber, int32 itemId);
	void UnEquip(EHOFItemType slotNumber);

	AHOFItem* GetEquippedItemBySlot(EHOFItemType slotNumber);

private : 
	TMap<EHOFItemType, AHOFItem*> EquipList;
	
};
