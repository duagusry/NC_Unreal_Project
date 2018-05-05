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
	//�̰� �ʹ� ������?
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

//������ CardActor���� ������ �ִ� �̺�Ʈ�� ������ �� ó���� ����ϴ� Ŭ����
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
	CardEventDialog& GetDialog() { return m_Dialog; }
	int32 GetSelectionResult(int32 id) { return m_Dialog.m_SelectionTexts[id - 1].Result; }
	FResult& GetEventResult(int32 id) { return m_Result.m_Results[id - 1]; }
	FReward& GetEventReward(int32 id) { return m_Reward.m_Rewards[id - 1]; }

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