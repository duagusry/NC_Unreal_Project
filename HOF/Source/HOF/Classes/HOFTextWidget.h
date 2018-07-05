// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData.h"
#include "UMG.h"
#include "HOFCardEvent.h"
#include "Blueprint/UserWidget.h"
#include "HOFGameInstance.h"
#include "HOFWorldCardActor.h"
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

	void Init(int32 id, AHOFWorldCardActor* pCard);

	bool IsWidgetActive() { return m_IsWidgetActive; }

private:
	void HandleEvent(int32 id, bool isSelection = true);
	
	void SetEvent(int32 eventId);

	void HandleReward(FReward reward);
	void HandleAnotherDialog(int32 dialogId);
	void HandleAnotherEvent(int32 eventId);
	void HandleTransfer(/* 이것저것 파라미터 */);
	void SetEnemyData();

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

	int32 m_CurrentDialogId;
	bool m_IsWidgetActive;
};
