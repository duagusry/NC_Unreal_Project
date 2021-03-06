// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData.h"
#include "UMG.h"
#include "HOFCardEvent.h"
#include "Blueprint/UserWidget.h"
#include "HOFTextWidget.generated.h"

using namespace SizeInGame;
using namespace NumberInGame;

class HOFCardEvent;
class AHOFWorldCardActor;
class UHOFGameInstance;
class AHOFPlayerState;
class AHOFGameState;

/**
 * 
 */
UCLASS()
class HOF_API UHOFTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public : 

	void Init(int32 id, AHOFWorldCardActor* pCard, int32 returnDialog = 1);
	
private:
	void HandleEvent(int32 id, bool isSelection = true);
	
	void SetWidgetFrame(int32 eventId);
	void CloseWidget();

	void HandleReward(FReward reward);
	void HandleAnotherDialog(int32 dialogId);
	void HandleAnotherEvent(int32 eventId);
	void HandleTransfer(const FBattleInfo& battleInfo);

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

	HOFCardEvent CardEvent;
	AHOFWorldCardActor* Card;
	UHOFGameInstance* GameInstance;
	AHOFPlayerState* PlayerState;
	AHOFGameState* GameState;

	int32 CurrentDialogId;
};
