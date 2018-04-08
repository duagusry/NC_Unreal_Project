#pragma once

#include "XmlParser.h"

struct FSelectionText
{
	FSelectionText()
		: Result(0), Text(L"")
	{ }

	int32 Result;
	FString Text;
};

class CardEventDialog
{
public : 
	void Parse(const FXmlNode* Node);

	TArray<FString> m_Texts;
	TArray<FSelectionText> m_SelectionTexts;
};

struct FResult
{
	FResult()
		: Id(0), Reward(0), Event(0), Transfer(false), Gambit(false)
	{ }

	int32 Id;
	int32 Reward;
	int32 Event;
	bool Transfer;
	bool Gambit;
};

class CardEventResult
{
public : 
	void Parse(const FXmlNode* Node);

private : 
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

private : 
	TArray<FReward> m_Rewards;
};

//각각의 CardActor들이 가지고 있는 이벤트의 종류와 그 처리를 담당하는 클래스
class HOFCardEvent
{
public:
	HOFCardEvent() { }
	HOFCardEvent(const HOFCardEvent& other);

	void SetID(int32 id) { m_Id = id; }
	void SetDialog(CardEventDialog& dialog) { m_Dialog = dialog; }
	void SetResult(CardEventResult& result) { m_Result = result; }
	void SetReward(CardEventReward& reward) { m_Reward = reward; }
	
	int32 GetID() { return m_Id; }

private : 
	int32 m_Id;
	CardEventDialog m_Dialog;
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

private : 
	TMap<int32, const HOFCardEvent> m_Map;

	CardEventResource() { }
	static CardEventResource* CardEventResourceInstance;
};

#define g_CardEvent CardEventResource::GetInstance()