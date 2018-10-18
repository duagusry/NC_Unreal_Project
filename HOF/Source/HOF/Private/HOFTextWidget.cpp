// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFTextWidget.h"
#include "HOFGameInstance.h"
#include "GameData.h"
#include "HOFCardEvent.h"
#include "EnemyResources.h"
#include "HOF.h"
#include "HOFWorldPlayerController.h"
#include "HOFWorldGameMode.h"
#include "HOFPlayerState.h"
#include "HOFGameState.h"

void UHOFTextWidget::OnSelection1Clicked()
{
	HandleEvent(1);
}

void UHOFTextWidget::OnSelection2Clicked()
{
	HandleEvent(2);
}

void UHOFTextWidget::OnSelection3Clicked()
{
	HandleEvent(3);
}

void UHOFTextWidget::OnSelection4Clicked()
{
	HandleEvent(4);
}

void UHOFTextWidget::OnNextClicked()
{
	//�ؽ�Ʈ�� �ִ� �⺻ �̺�Ʈ�� ó���ϰ� ���� ���̾�α׷� �̵�
	int32 CurrentDialogEvent = CardEvent.GetDialogEventResult(CurrentDialogId);
	CurrentDialogId = CardEvent.GetNextDialog(CurrentDialogId);

	HandleEvent(CurrentDialogEvent, false);

	if (CurrentDialogId)
	{
		SetWidgetFrame(CardEvent.GetID());
	}
	else
	{
		CloseWidget();
		GameState->SetState(GAME_WORLD);
	}
}

void UHOFTextWidget::Init(int32 id, AHOFWorldCardActor * pCard, int32 returnDialog)
{
	PlayerState = GetOwningPlayerState<AHOFPlayerState>(true);
	GameState = GetWorld()->GetAuthGameMode()->GetGameState<AHOFGameState>();
	GameInstance = Cast<UHOFGameInstance>(GetWorld()->GetGameInstance());

	CardEvent = g_CardEvent->GetCardEventFromId(id);
	Card = pCard;
	CurrentDialogId = returnDialog;

	// Fill texts, buttons to widget with eventId
	SetWidgetFrame(id);

	int Index = 1;
	//��ư�� Ŭ���� ����� �ڵ鷯 �Լ� ����
	for (Index; Index < MAX_SELECTION_COUNT; Index++)
	{
		UButton* SelectionButton = Cast<UButton>(Cast<UPanelWidget>(GetRootWidget())->GetChildAt(Index + NumberInGame::TEXT_BLOCK_START));

		switch (Index)
		{
		case 1:
			SelectionButton->OnClicked.AddDynamic(this, &UHOFTextWidget::OnSelection1Clicked);
			break;
		case 2:
			SelectionButton->OnClicked.AddDynamic(this, &UHOFTextWidget::OnSelection2Clicked);
			break;
		case 3:
			SelectionButton->OnClicked.AddDynamic(this, &UHOFTextWidget::OnSelection3Clicked);
			break;
		case 4:
			SelectionButton->OnClicked.AddDynamic(this, &UHOFTextWidget::OnSelection4Clicked);
			break;
		}
	}

	UButton* NextButton = Cast<UButton>(Cast<UPanelWidget>(GetRootWidget())->GetChildAt(Index + NumberInGame::TEXT_BLOCK_START + 1));
	NextButton->OnClicked.AddDynamic(this, &UHOFTextWidget::OnNextClicked);

	GameState->SetState(GAME_DIALOG);

	//�Ʒ��� WindowForm �����ϵ��� ���̾ƿ� �� ¥�� ��ư �ְ� �ؽ�Ʈ �ְ� �غ����� ������ �Ұ����� �� ����
	//��������� �ּ�ó���ؼ� ���ܳ���
	/*
	int textIndex = 0;

	for (auto it : CardEvent.GetDialog().m_Texts)
	{
		float positionX = WIDGET_POSITION_X;
		float positionY = WIDGET_POSITION_Y + (textIndex * WIDGET_SIZE_Y);
		float sizeX = WIDGET_SIZE_X;
		float sizeY = WIDGET_SIZE_Y;

		//�ؽ�Ʈ ����
		UTextBlock* newText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass()); // The second parameter is the name and is optional.
		newText->SetText(FText::FromString(it));

		//���� ��ġ
		UCanvasPanelSlot* textSlot = NewObject<UCanvasPanelSlot>(RootWidget->AddChild(newText));
		textSlot->Parent = RootWidget;
		textSlot->SetPosition(FVector2D(positionX, positionY));
		textSlot->SetSize(FVector2D(sizeX, sizeY));

		Texts.Add(newText);

		textIndex++;
	}

	int index = 1;

	for (auto it : CardEvent.GetDialog().m_SelectionTexts)
	{
		float positionX = WIDGET_POSITION_X;
		float positionY = WIDGET_POSITION_Y + (textIndex * WIDGET_SIZE_Y);
		float sizeX = WIDGET_SIZE_X;
		float sizeY = WIDGET_SIZE_Y;

		//���� ��ư ����
		FString text = it.Text;
		UButton* newSelectText = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), *FString::FromInt(index));
		newSelectText->SetBackgroundColor(FLinearColor(1, 1, 1, 0));
		// Ŭ�� �̺�Ʈ ���ε�
		//AddDynamic ��ũ�δ� �Լ� �̸� �޾Ƽ� �״�� ����ϱ⶧���� ���ٵ� �ȵǰ� �Լ������� �迭�� ȣ���ϴ°͵� �ȵ�. ������ �� �Լ��� �̸�.
		//�׸��� Onclicked �Լ� ��ü�� void f(void)�� Ÿ�� �����̶� �߰� �Ķ���͵� ���� �Ұ���
		switch (index)
		{
		case 1 : 
			newSelectText->OnClicked.AddDynamic(this, &UHOFTextWidget::OnSelection1Clicked);
			break;
		case 2:
			newSelectText->OnClicked.AddDynamic(this, &UHOFTextWidget::OnSelection2Clicked);
			break;
		case 3:
			newSelectText->OnClicked.AddDynamic(this, &UHOFTextWidget::OnSelection3Clicked);
			break;
		case 4:
			newSelectText->OnClicked.AddDynamic(this, &UHOFTextWidget::OnSelection4Clicked);
			break;
		}

		//��ư�� ���̴� �ؽ�Ʈ ����
		UTextBlock* newText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		newText->SetText(FText::FromString(text));
		newSelectText->AddChild(newText);

		//���� ��ġ
		UCanvasPanelSlot* textSlot = NewObject<UCanvasPanelSlot>(RootWidget->AddChild(newSelectText));
		textSlot->Parent = RootWidget;
		textSlot->SetPosition(FVector2D(positionX, positionY));
		textSlot->SetSize(FVector2D(sizeX, sizeY));

		SelectTexts.Add(newSelectText);

		index++;
		textIndex++;
	}
	*/
}

void UHOFTextWidget::HandleEvent(int32 id, bool isSelection /* = true */)
{
	//id�� 0�̸� ���� �̺�Ʈ
	if (!id)
		return;
	
	int32 resultId = isSelection ? CardEvent.GetDialog(CurrentDialogId).GetSelectionResult(id) : id;
	// TODO : It's better to make FResult Interface structure.
	//        e.g. Transfer result, gambit result, and so on. 
	FResult result = CardEvent.GetEventResult(resultId);
	bool IsEventEnd = false;
	
	if (result.Reward)
	{
		HandleReward(CardEvent.GetEventReward(result.Reward));
		if (!result.HasMultiResult())
			IsEventEnd = true;
	}

	if (result.Dialog)
	{
		HandleAnotherDialog(result.Dialog);
	}

	if (result.Gambit)
	{
		// ���� ���� ó���� �ʿ��ҵ�.. ����غ��ߵ�.
		// V1������ ���� �����ϴ°͵�..
		//IsEventEnd = true;
	}

	if (IsEventEnd)
	{
		CloseWidget();
		GameState->SetState(GAME_WORLD);
	}

}

void UHOFTextWidget::SetWidgetFrame(int32 eventId)
{
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	//Ÿ��Ʋ
	UTextBlock* Title = Cast<UTextBlock>(RootWidget->GetChildAt(1));
	Title->SetText(FText::FromString(CardEvent.GetTitle()));

	//���̾�α� �ؽ�Ʈ
	UTextBlock* TextBlock = Cast<UTextBlock>(RootWidget->GetChildAt(NumberInGame::TEXT_BLOCK_START));
	const CardEventDialog& DialogEvent = CardEvent.GetDialog(CurrentDialogId);
	TextBlock->SetText(FText::FromString(DialogEvent.Text.Text));

	bool HasSelection = false;
	int32 Index = 1;

	for (Index; Index <= DialogEvent.SelectionTextArray.Num(); Index++)
	{
		FText ButtonText = FText::FromString(DialogEvent.SelectionTextArray[Index - 1].Text);

		UButton* SelectionButton = Cast<UButton>(RootWidget->GetChildAt(Index + NumberInGame::TEXT_BLOCK_START));
		UTextBlock* SelectionText = Cast<UTextBlock>(SelectionButton->GetChildAt(0));
		SelectionText->SetText(ButtonText);
		SelectionButton->SetIsEnabled(true);

		HasSelection = true;
	}

	//���� ������ ��ư ��Ȱ��ȭ
	for (Index; Index <= MAX_SELECTION_COUNT; Index++)
	{
		UButton* SelectionButton = Cast<UButton>(RootWidget->GetChildAt(Index + NumberInGame::TEXT_BLOCK_START));
		UTextBlock* SelectionText = Cast<UTextBlock>(SelectionButton->GetChildAt(0));
		SelectionText->SetText(FText::FromString(""));
		SelectionButton->SetIsEnabled(false);
	}

	// '���' ��ư�� ���� ó��
	UButton* NextButton = Cast<UButton>(RootWidget->GetChildAt(Index + NumberInGame::TEXT_BLOCK_START));
	UTextBlock* NextText = Cast<UTextBlock>(NextButton->GetChildAt(0));

	//�������� ������ '���' ��ư ��Ȱ��ȭ, ������ '���' ��ư Ȱ��ȭ
	if (HasSelection)
	{
		NextButton->SetVisibility(ESlateVisibility::Hidden);
		NextButton->SetIsEnabled(false);
	}
	else
	{
		NextButton->SetVisibility(ESlateVisibility::Visible);
		NextButton->SetIsEnabled(true);
	}
}

void UHOFTextWidget::CloseWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UHOFTextWidget::HandleReward(FReward reward)
{
	if (reward.ItemArray.Num())
	{
		//������ ó��

	}

	if (reward.Food != 0)
	{
		PlayerState->ModifyFood(reward.Food);
	}

	if (reward.Gold != 0)
	{
		PlayerState->ModifyGold(reward.Gold);
	}

	if (reward.MaxHealth != 0)
	{
		PlayerState->ModifyMaxHP(reward.MaxHealth);
	}

	if (reward.CurrentHealth != 0)
	{
		PlayerState->ModifyCurrentHP(reward.CurrentHealth);
	}

	if (reward.Reveal > 0)
	{
		Cast<AHOFWorldGameMode>(GetWorld()->GetAuthGameMode())->HandleRevealEvent(reward.Reveal);
	}

	if (reward.Battle > 0)
	{
		const auto& BattleInfo = CardEvent.GetEventBattle(reward.Battle);
		HandleTransfer(BattleInfo);
	}
}

void UHOFTextWidget::HandleAnotherDialog(int32 dialogId)
{
	CurrentDialogId = dialogId;
	SetWidgetFrame(CardEvent.GetID());
}

void UHOFTextWidget::HandleAnotherEvent(int32 eventId)
{
	//������ ���� ����°� �ƴ϶� ��Ȱ��.
	CardEvent = g_CardEvent->GetCardEventFromId(eventId);
	SetWidgetFrame(eventId);
}

void UHOFTextWidget::HandleTransfer(const FBattleInfo& battleInfo)
{
	AB_LOG_CALLONLY(Warning);
	const auto& GameMode = Cast<AHOFWorldGameMode>(GetWorld()->GetAuthGameMode());

	BaseStructs::BattleData BattleParam;
	for (const auto& it : battleInfo.SpawnInfoArray)
	{
		BattleParam.SpawnInfo.Add(it.Type, it.Amount);
	}

	GameState->SetState(GAME_BATTLE);
	GameInstance->SetBattleData(BattleParam);
	GameInstance->PlayerData = BaseStructs::PlayerData{ PlayerState->PlayerData.HP, PlayerState->PlayerData.Food, PlayerState->PlayerData.Gold, PlayerState->PlayerData.Alive };
	GameInstance->SaveCurrentWorldStatusData(GameMode->AssignWorldStatusData(battleInfo.ReturnDialog));
	UGameplayStatics::OpenLevel(GetWorld(), "HOFBattleLevel");
}



