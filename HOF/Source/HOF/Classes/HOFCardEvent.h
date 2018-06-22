#pragma once

#include "XmlParser.h"

struct FNormalText
{
	FNormalText()
		: Result(0), Text(L"")
	{ }

	int32 Result;
	FString Text;
};

struct FSelectionText
{
	FSelectionText()
		: Result(0), Text(L"")
	{ }

	int32 Result;
	FString Text;
};

// Id, Next, FNormalText 한개, FSelectionText 다수
class CardEventDialog
{
public : 
	CardEventDialog()
		: m_Id(0), m_Next(0)
	{ }

	void Parse(const FXmlNode* Node);
	/*
	//리스트 맨 앞의 NormalText를 배정하고 NormalText가 더 남았는지 여부를 반환
	bool AssignNormalTextEvent(int32& id, FString& str)
	{
		if (!m_Texts.empty())
		{
			id = m_Texts.front().Result;
			str = m_Texts.front().Text;

			m_Texts.pop_front();
		}

		return !m_Texts.empty();
	}
	*/
	int32 GetSelectionResult(int32 id) { return m_SelectionTexts[id - 1].Result; }

	int32 m_Id;
	int32 m_Next;
	FNormalText m_Text;
	TArray<FSelectionText> m_SelectionTexts;
};

struct FResult
{
	FResult()
		: Id(0), Reward(0), Dialog(0), Transfer(false), Gambit(false)
	{ }

	bool HasMultiResult()
	{
		int32 counter = 0;

		if (Reward > 0)
			counter++;

		if (Dialog > 0)
			counter++;

		if (Transfer)
			counter++;

		if (Gambit)
			counter++;

		return counter > 0 ? true : false;
	}

	int32 Id;
	int32 Reward;
	int32 Dialog;
	bool Transfer;
	bool Gambit;
};

class CardEventResult
{
public : 
	void Parse(const FXmlNode* Node);

	TArray<FResult> m_Results;
};

struct FItem
{
	FItem()
		: Id(0), Amount(0)
	{ }

	int32 Id;
	int32 Amount;
};

struct FReward
{
	//이건 너무 많은데?
	FReward()
		: Id(0), Food(0), Gold(0), MaxHealth(0), CurrentHealth(0)
	{ }

	int32 Id;
	TArray<FItem> ItemList;
	int32 Food;
	int32 Gold;
	int32 MaxHealth;
	int32 CurrentHealth;
};

class CardEventReward
{
public : 
	void Parse(const FXmlNode* Node);

	TArray<FReward> m_Rewards;
};

//각각의 CardActor들이 가지고 있는 이벤트의 종류와 그 처리를 담당하는 클래스
class HOFCardEvent
{
public:
	HOFCardEvent() { }
	HOFCardEvent(const HOFCardEvent& other);

	void SetID(int32 id) { m_Id = id; }
	void SetTitle(FString title) { m_Title = title; }
	void AddDialog(CardEventDialog& dialog) { m_Dialogs.Add(dialog.m_Id, dialog); }
	void SetResult(CardEventResult& result) { m_Result = result; }
	void SetReward(CardEventReward& reward) { m_Reward = reward; }
	
	int32 GetID() { return m_Id; }
	FString GetTitle() { return m_Title; }
	CardEventDialog& GetDialog(int32 index) { return m_Dialogs[index]; }
	FResult& GetEventResult(int32 id) { return m_Result.m_Results[id - 1]; }
	FReward& GetEventReward(int32 id) { return m_Reward.m_Rewards[id - 1]; }

	int32 GetNextDialog(int32 index) { return m_Dialogs[index].m_Next; }
	int32 GetDialogEventResult(int32 index) { return m_Dialogs[index].m_Text.Result; }

private : 
	int32 m_Id;
	FString m_Title;
	TMap<int32, CardEventDialog> m_Dialogs;
	CardEventResult m_Result;
	CardEventReward m_Reward;
};

class CardEventResource
{
public : 
	void Parse(const FString dir);

	static CardEventResource* GetInstance()
	{
		if (!CardEventResourceInstance)
			CardEventResourceInstance = new CardEventResource();

		return CardEventResourceInstance;
	}

	const HOFCardEvent GetCardEventFromId(int32 id);

	void AssignEventArray(TArray<int32>& eventArray)
	{

		for (auto cardEvent : m_Map)
		{
			eventArray.Add(cardEvent.Key);
		}
	}

private : 
	TMap<int32, const HOFCardEvent> m_Map;

	CardEventResource() { }
	static CardEventResource* CardEventResourceInstance;
};

#define g_CardEvent CardEventResource::GetInstance()