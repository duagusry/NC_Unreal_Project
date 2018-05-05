// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFTextWidget.h"
#include "HOFGameInstance.h"
#include "GameData.h"
#include "PlayerData.h"
#include "HOFCardEvent.h"
#include "HOFWorldPlayerController.h"

void UHOFTextWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

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

void UHOFTextWidget::Init(int32 id)
{
	//������ ǥ�õǴ� �ؽ�Ʈ�� ����
	SetEvent(id);

	//��ư�� Ŭ���� ����� �ڵ鷯 �Լ� ����
	for (int i = 1; i < MAX_SELECTION_COUNT; i++)
	{
		UButton* SelectionButton = Cast<UButton>(Cast<UPanelWidget>(GetRootWidget())->GetChildAt(i + 1));

		switch (i)
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

void UHOFTextWidget::HandleEvent(int32 id)
{
	int32 resultId = m_CardEvent.GetSelectionResult(id);
	FResult result = m_CardEvent.GetEventResult(resultId);

	if (result.Reward)
	{
		HandleReward(m_CardEvent.GetEventReward(result.Reward));
		SetVisibility(ESlateVisibility::Hidden);
	}

	if (result.Event)
	{
		HandleAnotherEvent(result.Event);
	}

	if (result.Transfer)
	{
		HandleTransfer();
		SetVisibility(ESlateVisibility::Hidden);
	}

	if (result.Gambit)
	{

		SetVisibility(ESlateVisibility::Hidden);
	}

}

void UHOFTextWidget::SetEvent(int32 eventId)
{
	m_CardEvent = g_CardEvent->GetCardEventFromId(eventId);
	
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	//���̾�α� �ؽ�Ʈ
	UTextBlock* TextBlock = Cast<UTextBlock>(RootWidget->GetChildAt(1));

	FString Dialog = "";

	for (auto it : m_CardEvent.GetDialog().m_Texts)
	{
		Dialog += it + "\n";
	}

	TextBlock->SetText(FText::FromString(Dialog));

	int32 index = 1;

	for (index; index <= m_CardEvent.GetDialog().m_SelectionTexts.Num(); index++)
	{
		FText ButtonText = FText::FromString(m_CardEvent.GetDialog().m_SelectionTexts[index - 1].Text);

		UButton* SelectionButton = Cast<UButton>(RootWidget->GetChildAt(index + 1));
		UTextBlock* SelectionText = Cast<UTextBlock>(SelectionButton->GetChildAt(0));
		SelectionText->SetText(ButtonText);
	}

	//���� ������ ��ư ��Ȱ��ȭ
	for (index; index <= MAX_SELECTION_COUNT; index++)
	{
		UButton* SelectionButton = Cast<UButton>(RootWidget->GetChildAt(index + 1));
		UTextBlock* SelectionText = Cast<UTextBlock>(SelectionButton->GetChildAt(0));
		SelectionText->SetText(FText::FromString(""));
		SelectionButton->SetIsEnabled(false);
	}
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
		g_PlayerData->GainFood(reward.Food);
	}
	else if (reward.Food < 0)
	{
		g_PlayerData->LoseFood(reward.Food);
	}

	if (reward.Gold > 0)
	{
		g_PlayerData->GainGold(reward.Gold);
	}
	else if (reward.Gold < 0)
	{
		g_PlayerData->LoseGold(reward.Gold);
	}

	if (reward.MaxHealth > 0)
	{
		g_PlayerData->GainMaxHealth(reward.MaxHealth);
	}
	else if (reward.MaxHealth < 0)
	{
		g_PlayerData->LoseMaxHealth(reward.MaxHealth);
	}

	if (reward.CurrentHealth > 0)
	{
		g_PlayerData->GainCurrentHealth(reward.CurrentHealth);
	}
	else if (reward.CurrentHealth < 0)
	{
		g_PlayerData->LoseCurrentHealth(reward.CurrentHealth);
	}
}

void UHOFTextWidget::HandleAnotherEvent(int32 eventId)
{
	//������ ���� ����°� �ƴ϶� ��Ȱ��.
	this->SetEvent(eventId);
}

void UHOFTextWidget::HandleTransfer()
{
	Cast<UHOFGameInstance>(GetWorld()->GetGameInstance())->SwitchToBattle(FString("/Game/Maps/HOFBattleLevel"));
}


