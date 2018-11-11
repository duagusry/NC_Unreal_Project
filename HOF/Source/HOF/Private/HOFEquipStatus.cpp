// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFEquipStatus.h"
#include "HOFItem.h"
#include "HOFGearItem.h"
#include "HOFItemResource.h"


// Sets default values
AHOFEquipStatus::AHOFEquipStatus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EquipList.Init(nullptr, EnumInGame::EHOFItemType::ITEM_TYPE_END);
}

AHOFEquipStatus::~AHOFEquipStatus()
{
	// 장착 상태 초기화
	for (auto item : EquipList)
	{
		item = nullptr;
	}
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

void AHOFEquipStatus::Equip(EnumInGame::EHOFItemType slotNumber, TSharedPtr<AHOFItem> item)
{
	EquipList[slotNumber] = item;
}

void AHOFEquipStatus::Equip(EnumInGame::EHOFItemType slotNumber, AHOFItem * item)
{
	EquipList[slotNumber] = MakeShareable<AHOFItem>(item);
}

void AHOFEquipStatus::Equip(EnumInGame::EHOFItemType slotNumber, int32 itemId)
{
	EquipList[slotNumber] = (g_ItemResource->GetItemFromId(itemId));
}

void AHOFEquipStatus::UnEquip(EnumInGame::EHOFItemType slotNumber)
{
	EquipList[slotNumber] = nullptr;
}

TSharedPtr<AHOFItem> AHOFEquipStatus::GetEquippedItemWithSlot(EnumInGame::EHOFItemType slotNumber)
{
	if (!EquipList[slotNumber].IsValid())
		return nullptr;

	if (EquipList[slotNumber]->IsGearItem())
		return EquipList[slotNumber];
	else
		return nullptr;
}



