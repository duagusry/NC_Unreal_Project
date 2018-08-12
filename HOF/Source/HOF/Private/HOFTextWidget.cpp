// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFTextWidget.h"
#include "HOFGameInstance.h"
#include "GameData.h"
#include "HOFCardEvent.h"
#include "EnemyData.h"
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
	//텍스트에 있는 기본 이벤트를 처리하고 다음 다이얼로그로 이동
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

void UHOFTextWidget::Init(int32 id, AHOFWorldCardActor * pCard, int32 returnDialog)
{
	PlayerState = GetOwningPlayerState<AHOFPlayerState>(true);
	GameState = GetWorld()->GetAuthGameMode()->GetGameState<AHOFGameState>();

	m_CardEvent = g_CardEvent->GetCardEventFromId(id);
	m_Card = pCard;
	m_CurrentDialogId = returnDialog;

	//위젯에 표시되는 텍스트들 세팅
	SetEvent(id);

	int index = 1;
	//버튼에 클릭시 실행될 핸들러 함수 연결
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

void UHOFTextWidget::HandleEvent(int32 id, bool isSelection /* = true */)
{
	//id가 0이면 없는 이벤트
	if (!id)
		return;
	
	int32 resultId = isSelection ? m_CardEvent.GetDialog(m_CurrentDialogId).GetSelectionResult(id) : id;
	// TODO : It's better to make FResult Interface structure.
	//        e.g. Transfer result, gambit result, and so on. 
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

	if (result.Gambit)
	{
		// 뭔가 별도 처리가 필요할듯.. 고민해봐야됨.
		// V1에서는 갬빗 제외하는것도..
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

	//타이틀
	UTextBlock* Title = Cast<UTextBlock>(RootWidget->GetChildAt(1));
	Title->SetText(FText::FromString(m_CardEvent.GetTitle()));

	//다이얼로그 텍스트
	UTextBlock* TextBlock = Cast<UTextBlock>(RootWidget->GetChildAt(NumberInGame::TEXT_BLOCK_START));
	CardEventDialog& DialogEvent =  m_CardEvent.GetDialog(m_CurrentDialogId);
	TextBlock->SetText(FText::FromString(DialogEvent.Text.Text));
	
	int32 index = 1;

	for (index; index <= DialogEvent.SelectionTextArray.Num(); index++)
	{
		FText ButtonText = FText::FromString(DialogEvent.SelectionTextArray[index - 1].Text);

		UButton* SelectionButton = Cast<UButton>(RootWidget->GetChildAt(index + NumberInGame::TEXT_BLOCK_START));
		UTextBlock* SelectionText = Cast<UTextBlock>(SelectionButton->GetChildAt(0));
		SelectionText->SetText(ButtonText);
		SelectionButton->SetIsEnabled(true);

		hasSelection = true;
	}

	//남는 선택지 버튼 비활성화
	for (index; index <= MAX_SELECTION_COUNT; index++)
	{
		UButton* SelectionButton = Cast<UButton>(RootWidget->GetChildAt(index + NumberInGame::TEXT_BLOCK_START));
		UTextBlock* SelectionText = Cast<UTextBlock>(SelectionButton->GetChildAt(0));
		SelectionText->SetText(FText::FromString(""));
		SelectionButton->SetIsEnabled(false);
	}

	// '계속' 버튼에 대한 처리
	UButton* NextButton = Cast<UButton>(RootWidget->GetChildAt(index + NumberInGame::TEXT_BLOCK_START));
	UTextBlock* NextText = Cast<UTextBlock>(NextButton->GetChildAt(0));

	//선택지가 있으면 '계속' 버튼 비활성화, 없으면 '계속' 버튼 활성화
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

void UHOFTextWidget::HandleReward(FReward reward)
{
	if (reward.ItemArray.Num())
	{
		//아이템 처리
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
		const auto& BattleInfo = m_CardEvent.GetEventBattle(reward.Battle);
		HandleTransfer(BattleInfo);
	}
}

void UHOFTextWidget::HandleAnotherDialog(int32 dialogId)
{
	m_CurrentDialogId = dialogId;
	SetEvent(m_CardEvent.GetID());
}

void UHOFTextWidget::HandleAnotherEvent(int32 eventId)
{
	//위젯은 새로 만드는게 아니라 재활용.
	m_CardEvent = g_CardEvent->GetCardEventFromId(eventId);
	SetEvent(eventId);
}

void UHOFTextWidget::HandleTransfer(const FBattleInfo& battleInfo)
{
	AB_LOG_CALLONLY(Warning);
	auto gameInstance = Cast<UHOFGameInstance>(GetWorld()->GetGameInstance());
	auto enemyData = gameInstance->GetEnemyData();
	auto gameMode = Cast<AHOFWorldGameMode>(GetWorld()->GetAuthGameMode());

	BaseStructs::BattleData BattleParam;
	for (auto it : battleInfo.SpawnInfoArray)
	{
		BattleParam.SpawnInfo.Add(it.Type, it.Amount);
	}

	GameState->SetState(GAME_BATTLE);
	gameInstance->SetBattleData(BattleParam);

	enemyData->SetEnemyData(battleInfo.SpawnInfoArray[0].Type, battleInfo.SpawnInfoArray[0].Amount);
	gameInstance->PlayerData = BaseStructs::PlayerData{ PlayerState->PlayerData.HP, PlayerState->PlayerData.Food, PlayerState->PlayerData.Gold, PlayerState->PlayerData.Alive };
	gameInstance->SaveCurrentWorldStatusData(gameMode->AssignWorldStatusData(battleInfo.ReturnDialog));
	UGameplayStatics::OpenLevel(GetWorld(), "HOFBattleLevel");
}



