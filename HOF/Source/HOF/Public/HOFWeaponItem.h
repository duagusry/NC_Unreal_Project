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
	virtual bool IsWeaponItem() override { return true; }

	inline float GetAttackDamage() { return Damage; }

protected : 
	float Damage;
	float Range;
	float AtttackSpeed;
	EnumInGame::EHOFElement Element;
	float CriticalProb;
	int32 SpellId;
	
};
