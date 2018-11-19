// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HOFItem.generated.h"

UCLASS()
class HOF_API AHOFItem : public AActor
{
public:
	GENERATED_BODY()
	
	// Sets default values for this actor's properties
	AHOFItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool IsGearItem() { return false; }
	virtual bool IsWeaponItem() { return false; }
	
	UPROPERTY()
	int32 Id;

	UPROPERTY()
	FName Name;
	
	UPROPERTY()
	int32 BuyCost;
	
	UPROPERTY()
	int32 SellCost;
	
	UPROPERTY()
	bool CanSell;

	UPROPERTY()
    FString AssetPath;
};
