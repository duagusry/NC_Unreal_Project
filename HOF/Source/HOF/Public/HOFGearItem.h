// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HOFItem.h"
#include "GameData.h"
#include "HOFGearItem.generated.h"

/**
 * 
 */
UCLASS()
class HOF_API AHOFGearItem : public AHOFItem
{
	GENERATED_BODY()
	
public : 
	virtual bool IsGearItem() override { return true; }

protected:
	EnumInGame::EHOFItemType Type;
	
	
};
