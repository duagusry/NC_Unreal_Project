// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData.h"
#include "UMG.h"
#include "HOFCardEvent.h"
#include "Blueprint/UserWidget.h"
#include "HOFGameInstance.h"
#include "HOFTextWidget.generated.h"

using namespace SizeInGame;
using namespace NumberInGame;

/**
 * 
 */
UCLASS()
class HOF_API UHOFTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public : 
	virtual void NativeConstruct() override;

	void Init(int32 id);

private:
	void HandleEvent(int32 id);
	
	void SetEvent(int32 eventId);

	void HandleReward(FReward reward);
	void HandleAnotherEvent(int32 eventId);
	void HandleTransfer(/* 이것저것 파라미터 */);

	UFUNCTION()
		void OnSelection1Clicked();

	UFUNCTION()
		void OnSelection2Clicked();

	UFUNCTION()
		void OnSelection3Clicked();

	UFUNCTION()
		void OnSelection4Clicked();

	HOFCardEvent m_CardEvent;
	UHOFGameInstance* GameInstance;
};
