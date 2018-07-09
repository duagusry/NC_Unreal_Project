// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData.h"
#include "UMG.h"
#include "HOFCardEvent.h"
#include "Blueprint/UserWidget.h"
#include "HOFGameInstance.h"
#include "HOFWorldCardActor.h"
#include "HOFGameState.h"
#include "HOFPlayerState.h"
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

	void Init(int32 id, AHOFWorldCardActor* pCard);
	
private:
	void HandleEvent(int32 id, bool isSelection = true);
	
	void SetEvent(int32 eventId);
	void CloseWidget(EHOFGameState newState);

	void HandleReward(FReward reward);
	void HandleAnotherDialog(int32 dialogId);
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

	UFUNCTION()
		void OnNextClicked();

	HOFCardEvent m_CardEvent;
	AHOFWorldCardActor* m_Card;
	UHOFGameInstance* GameInstance;
	AHOFPlayerState* PlayerState;
	AHOFGameState* GameState;

	int32 m_CurrentDialogId;
};
