// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlayerData.h"
#include "GameData.h"
#include "HOFGameInstance.h"
#include "HOFWorldGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HOF_API AHOFWorldGameMode : public AGameMode
{
	GENERATED_BODY()
	
public : 
	AHOFWorldGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void InitGameState() override;

	void OnTimerTick();
	

private : 
	TUniquePtr<FPlayerData> PlayerData;
	UHOFGameInstance* GameInstance;
	
	UPROPERTY(EditAnywhere)
	int32 Counter;
	FTimerHandle countDownHandle;

};
