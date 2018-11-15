// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFEquipStatus.h"
#include "HOFItem.h"
#include "HOFGearItem.h"
#include "HOFGameInstance.h"
#include "HOFItemResource.h"


// Sets default values
AHOFEquipStatus::AHOFEquipStatus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHOFEquipStatus::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHOFEquipStatus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHOFEquipStatus::Equip(EHOFItemType slotNumber, AHOFItem * item)
{
	if (EquipList.Contains(slotNumber))
		EquipList[slotNumber] = item;
	else
		EquipList.Add(slotNumber, item);
}

void AHOFEquipStatus::Equip(EHOFItemType slotNumber, int32 itemId)
{
	auto GameInstance = Cast<UHOFGameInstance>(GetGameInstance());

	if (EquipList.Contains(slotNumber))
		EquipList[slotNumber] = GameInstance->ItemResource->GetItemFromId(itemId);
	else
		EquipList.Add(slotNumber, GameInstance->ItemResource->GetItemFromId(itemId));
}

void AHOFEquipStatus::UnEquip(EHOFItemType slotNumber)
{
	EquipList.Remove(slotNumber);
}

AHOFItem* AHOFEquipStatus::GetEquippedItemWithSlot(EHOFItemType slotNumber)
{
	if (EquipList[slotNumber]->IsGearItem())
		return EquipList[slotNumber];
	else
		return nullptr;
}



