// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HOFGearItem.h"
#include "HOFWeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class HOF_API AHOFWeaponItem : public AHOFGearItem
{
	GENERATED_BODY()
	
public : 
	AHOFWeaponItem() {}
	virtual bool IsWeaponItem() override { return true; }

	inline float GetAttackDamage() { return Damage; }

	UPROPERTY()
		float Damage = 30.0f;
	
	UPROPERTY()
	float Range;
	
	UPROPERTY()
	float AtttackSpeed;
	
	UPROPERTY()
	TEnumAsByte<EHOFElement> Element;
	
	UPROPERTY()
	float CriticalProb;
	
	UPROPERTY()
	int32 SpellId;
};
