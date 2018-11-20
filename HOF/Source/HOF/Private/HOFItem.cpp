// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFItem.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AHOFItem::AHOFItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = nullptr;
}

AHOFItem::AHOFItem(const AHOFItem & ref)
{
	Id = ref.Id;
	Name = ref.Name;
	BuyCost = ref.BuyCost;
	SellCost = ref.SellCost;
	CanSell = ref.CanSell;
}

AHOFItem& AHOFItem::operator=(const AHOFItem & ref)
{
	Id = ref.Id;
	Name = ref.Name;
	BuyCost = ref.BuyCost;
	SellCost = ref.SellCost;
	CanSell = ref.CanSell;

	return *this;
}

// Called when the game starts or when spawned
void AHOFItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHOFItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USkeletalMesh* AHOFItem::GetMesh()
{
	return Mesh;
}
