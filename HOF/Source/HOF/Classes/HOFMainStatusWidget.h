// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG.h"
#include "Blueprint/UserWidget.h"
#include "GameData.h"
#include "HOFMainStatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class HOF_API UHOFMainStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public : 

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
private : 	
};
