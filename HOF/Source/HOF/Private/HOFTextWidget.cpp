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
	//위젯에 표시되는 텍스트들 세팅
	SetEvent(id);

	//버튼에 클릭시 실행될 핸들러 함수 연결
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

	//아래는 WindowForm 개발하듯이 레이아웃 다 짜서 버튼 넣고 텍스트 넣고 해보려고 했으나 불가능한 것 같음
	//참고용으로 주석처리해서 남겨놓음
	/*
	int textIndex = 0;

	for (auto it : m_CardEvent.GetDialog().m_Texts)
	{
		float positionX = WIDGET_POSITION_X;
		float positionY = WIDGET_POSITION_Y + (textIndex * WIDGET_SIZE_Y);
		float sizeX = WIDGET_SIZE_X;
		float sizeY = WIDGET_SIZE_Y;

		//텍스트 생성
		UTextBlock* newText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass()); // The second parameter is the name and is optional.
		newText->SetText(FText::FromString(it));

		//슬롯 배치
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

		//선택 버튼 생성
		FString text = it.Text;
		UButton* newSelectText = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), *FString::FromInt(index));
		newSelectText->SetBackgroundColor(FLinearColor(1, 1, 1, 0));
		// 클릭 이벤트 바인딩
		//AddDynamic 매크로는 함수 이름 받아서 그대로 등록하기때문에 람다도 안되고 함수포인터 배열로 호출하는것도 안됨. 무조건 그 함수의 이름.
		//그리고 Onclicked 함수 자체가 void f(void)로 타입 고정이라서 추가 파라미터도 전달 불가능
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

		//버튼에 보이는 텍스트 생성
		UTextBlock* newText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		newText->SetText(FText::FromString(text));
		newSelectText->AddChild(newText);

		//슬롯 배치
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

	//다이얼로그 텍스트
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

	//남는 선택지 버튼 비활성화
	for (index; index <= MAX_SELECTION_COUNT; index++)
	{
		UButton* SelectionButton = Cast<UButton>(RootWidget->GetChildAt(index + 1));
		UTextBlock* SelectionText = Cast<UTextBlock>(SelectionButton->GetChildAt(0));
		SelectionText->SetText(FText::FromString(""));
		SelectionButton->SetIsEnabled(false);
	}
}

//코드 더러움
void UHOFTextWidget::HandleReward(FReward reward)
{
	if (reward.ItemList.Num())
	{
		//아이템 처리
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
	//위젯은 새로 만드는게 아니라 재활용.
	this->SetEvent(eventId);
}

void UHOFTextWidget::HandleTransfer()
{
	Cast<UHOFGameInstance>(GetWorld()->GetGameInstance())->SwitchToBattle(FString("/Game/Maps/HOFBattleLevel"));
}


