// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFMainStatusWidget.h"
#include "HOFPlayerState.h"
#include "GameData.h"

void UHOFMainStatusWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	auto PlayerState = Cast<AHOFPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);

	auto CurrentHPText = Cast<UTextBlock>(WidgetTree->FindWidget(L"Text_Current_HP"));
	CurrentHPText->SetText(FText::AsNumber(PlayerState->PlayerData.HP.GetCurrentValue()));

	auto MaxHPText = Cast<UTextBlock>(WidgetTree->FindWidget(L"Text_Max_HP"));
	MaxHPText->SetText(FText::AsNumber(PlayerState->PlayerData.HP.GetMaxValue()));

	auto HPBar = Cast<UProgressBar>(WidgetTree->FindWidget(L"ProgressBar_HP"));
	HPBar->SetPercent(PlayerState->PlayerData.HP.GetCurrentValue() / PlayerState->PlayerData.HP.GetMaxValue());

	auto FoodText = Cast<UTextBlock>(WidgetTree->FindWidget(L"Text_Food"));
	FoodText->SetText(FText::AsNumber(PlayerState->PlayerData.Food.GetCurrentValue()));

	auto GoldText = Cast<UTextBlock>(WidgetTree->FindWidget(L"Text_Gold"));
	GoldText->SetText(FText::AsNumber(PlayerState->PlayerData.Gold.GetCurrentValue()));
}
