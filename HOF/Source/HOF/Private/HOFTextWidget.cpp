// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFTextWidget.h"
#include "HOFGameInstance.h"
#include "GameData.h"
#include "HOFCardEvent.h"
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
	int32 currentDialogEvent = m_CardEvent.GetDialogEventResult(m_CurrentDialogId);
	m_CurrentDialogId = m_CardEvent.GetNextDialog(m_CurrentDialogId);

	HandleEvent(currentDialogEvent, false);

	if (m_CurrentDialogId)
	{
		SetEvent(m_CardEvent.GetID());
	}
	else
	{
		CloseWidget(GAME_WORLD);
	}
}

void UHOFTextWidget::Init(int32 id, AHOFWorldCardActor * pCard)
{
	PlayerState = GetOwningPlayerState<AHOFPlayerState>(true);
	GameState = GetWorld()->GetAuthGameMode()->GetGameState<AHOFGameState>();

	m_CardEvent = g_CardEvent->GetCardEventFromId(id);
	m_Card = pCard;
	m_CurrentDialogId = 1;

	//������ ǥ�õǴ� �ؽ�Ʈ�� ����
	SetEvent(id);

	int index = 1;
	//��ư�� Ŭ���� ����� �ڵ鷯 �Լ� ����
	for (index; index < MAX_SELECTION_COUNT; index++)
	{
		UButton* SelectionButton = Cast<UButton>(Cast<UPanelWidget>(GetRootWidget())->GetChildAt(index + NumberInGame::TEXT_BLOCK_START));

		switch (index)
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

	UButton* NextButton = Cast<UButton>(Cast<UPanelWidget>(GetRootWidget())->GetChildAt(index + NumberInGame::TEXT_BLOCK_START + 1));
	NextButton->OnClicked.AddDynamic(this, &UHOFTextWidget::OnNextClicked);

	GameState->SetState(GAME_DIALOG);

	//�Ʒ��� WindowForm �����ϵ��� ���̾ƿ� �� ¥�� ��ư �ְ� �ؽ�Ʈ �ְ� �غ����� ������ �Ұ����� �� ����
	//��������� �ּ�ó���ؼ� ���ܳ���
	/*
	int textIndex = 0;

	for (auto it : m_CardEvent.GetDialog().m_Texts)
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

	for (auto it : m_CardEvent.GetDialog().m_SelectionTexts)
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
	
	int32 resultId = isSelection ? m_CardEvent.GetDialog(m_CurrentDialogId).GetSelectionResult(id) : id;
	FResult result = m_CardEvent.GetEventResult(resultId);
	bool IsEventEnd = false;
	
	if (result.Reward)
	{
		HandleReward(m_CardEvent.GetEventReward(result.Reward));
		if (!result.HasMultiResult())
			IsEventEnd = true;
	}

	if (result.Dialog)
	{
		HandleAnotherDialog(result.Dialog);
	}

	if (result.Transfer)
	{
		HandleTransfer(); 
		IsEventEnd = true;
	}

	if (result.Gambit)
	{
		// ���� ���� ó���� �ʿ��ҵ�.. ����غ��ߵ�.
		// V1������ ���� �����ϴ°͵�..
		//IsEventEnd = true;
	}

	if (IsEventEnd)
	{
		CloseWidget(GAME_WORLD);
	}

}

void UHOFTextWidget::SetEvent(int32 eventId)
{
	bool hasSelection = false;
	
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	//Ÿ��Ʋ
	UTextBlock* Title = Cast<UTextBlock>(RootWidget->GetChildAt(1));
	Title->SetText(FText::FromString(m_CardEvent.GetTitle()));

	//���̾�α� �ؽ�Ʈ
	UTextBlock* TextBlock = Cast<UTextBlock>(RootWidget->GetChildAt(NumberInGame::TEXT_BLOCK_START));
	CardEventDialog& DialogEvent =  m_CardEvent.GetDialog(m_CurrentDialogId);
	TextBlock->SetText(FText::FromString(DialogEvent.m_Text.Text));
	
	int32 index = 1;

	for (index; index <= DialogEvent.m_SelectionTexts.Num(); index++)
	{
		FText ButtonText = FText::FromString(DialogEvent.m_SelectionTexts[index - 1].Text);

		UButton* SelectionButton = Cast<UButton>(RootWidget->GetChildAt(index + NumberInGame::TEXT_BLOCK_START));
		UTextBlock* SelectionText = Cast<UTextBlock>(SelectionButton->GetChildAt(0));
		SelectionText->SetText(ButtonText);
		SelectionButton->SetIsEnabled(true);

		hasSelection = true;
	}

	//���� ������ ��ư ��Ȱ��ȭ
	for (index; index <= MAX_SELECTION_COUNT; index++)
	{
		UButton* SelectionButton = Cast<UButton>(RootWidget->GetChildAt(index + NumberInGame::TEXT_BLOCK_START));
		UTextBlock* SelectionText = Cast<UTextBlock>(SelectionButton->GetChildAt(0));
		SelectionText->SetText(FText::FromString(""));
		SelectionButton->SetIsEnabled(false);
	}

	// '���' ��ư�� ���� ó��
	UButton* NextButton = Cast<UButton>(RootWidget->GetChildAt(index + NumberInGame::TEXT_BLOCK_START));
	UTextBlock* NextText = Cast<UTextBlock>(NextButton->GetChildAt(0));

	//�������� ������ '���' ��ư ��Ȱ��ȭ, ������ '���' ��ư Ȱ��ȭ
	if (hasSelection)
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

void UHOFTextWidget::CloseWidget(EHOFGameState newState)
{
	SetVisibility(ESlateVisibility::Hidden);
	GameState->SetState(newState);
}

//�ڵ� ������
void UHOFTextWidget::HandleReward(FReward reward)
{
	if (reward.ItemList.Num())
	{
		//������ ó��
	}

	if (reward.Food > 0)
	{
		PlayerState->GainFood(reward.Food);
	}
	else if (reward.Food < 0)
	{
		PlayerState->LoseFood(reward.Food);
	}

	if (reward.Gold > 0)
	{
		PlayerState->GainGold(reward.Gold);
	}
	else if (reward.Gold < 0)
	{
		PlayerState->LoseGold(reward.Gold);
	}

	if (reward.MaxHealth > 0)
	{
		PlayerState->GainMaxHP(reward.MaxHealth);
	}
	else if (reward.MaxHealth < 0)
	{
		PlayerState->LoseMaxHP(reward.MaxHealth);
	}

	if (reward.CurrentHealth > 0)
	{
		PlayerState->GainCurrentHP(reward.CurrentHealth);
	}
	else if (reward.CurrentHealth < 0)
	{
		PlayerState->LoseCurrentHP(reward.CurrentHealth);
	}

	if (reward.Reveal > 0)
	{
		Cast<AHOFWorldGameMode>(GetWorld()->GetAuthGameMode())->HandleRevealEvent(reward.Reveal);
	}

	if (reward.Battle > 0)
	{
		FBattleInfo& BattleInfo = m_CardEvent.GetEventBattle(reward.Battle);

		BattleTransferParameter param;
		param.EnemyCount = BattleInfo.Enemy;
		param.ReturnDialog = BattleInfo.ReturnDialog;

		Cast<UHOFGameInstance>(GetWorld()->GetGameInstance())->SetBattleParameter(param);
		GameState->SetState(GAME_BATTLE);
		HandleTransfer();
	}
}

void UHOFTextWidget::HandleAnotherDialog(int32 dialogId)
{
	m_CurrentDialogId = dialogId;
	SetEvent(m_CardEvent.GetID());
}

void UHOFTextWidget::HandleAnotherEvent(int32 eventId)
{
	//������ ���� ����°� �ƴ϶� ��Ȱ��.
	m_CardEvent = g_CardEvent->GetCardEventFromId(eventId);
	SetEvent(eventId);
}

void UHOFTextWidget::HandleTransfer()
{
	Cast<UHOFGameInstance>(GetWorld()->GetGameInstance())->SwitchToBattle(FString("/Game/Maps/HOFBattleLevel"));
}


