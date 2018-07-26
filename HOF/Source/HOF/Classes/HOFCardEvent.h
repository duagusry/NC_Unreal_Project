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

// Id, Next, FNormalText �Ѱ�, FSelectionText �ټ�
class CardEventDialog
{
public : 
	CardEventDialog()
		: m_Id(0), m_Next(0)
	{ }

	void Parse(const FXmlNode* Node);
	
	int32 GetSelectionResult(int32 id) { return m_SelectionTexts[id - 1].Result; }

	int32 m_Id;
	int32 m_Next;
	FNormalText m_Text;
	TArray<FSelectionText> m_SelectionTexts;
};

struct FResult
{
	FResult()
		: Id(0), Reward(0), Dialog(0), Gambit(false)
	{ }

	bool HasMultiResult()
	{
		int32 counter = 0;

		if (Reward > 0)
			counter++;

		if (Dialog > 0)
			counter++;
		
		if (Gambit)
			counter++;

		return counter > 0 ? true : false;
	}

	int32 Id;
	int32 Reward;
	int32 Dialog;
	bool Gambit;
};

class CardEventResult
{
public : 
	void Parse(const FXmlNode* Node);


	TArray<FResult> m_Results;

private:
	bool IsChildNodeName(const FXmlNode * node, FString tagName);
	FString GetAttribute(FXmlNode * node, FString attrName);
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
	// ��Ʈ�÷��׷� �����ϴ� �͵� �����ڴ�.
	FReward()
		: Id(0), Food(0), Gold(0), MaxHealth(0), CurrentHealth(0), Reveal(0), Battle(0)
	{ }

	int32 Id;
	TArray<FItem> ItemList;
	int32 Food;
	int32 Gold;
	int32 MaxHealth;
	int32 CurrentHealth;
	int32 Reveal;
	int32 Battle;
};

class CardEventReward
{
public : 
	void Parse(const FXmlNode* Node);

	TArray<FReward> m_Rewards;
};

struct FSpawnInfo
{
	FString Type;
	int32 amount;
};

struct FBattleInfo
{
	int32 Id;
	int32 ReturnDialog;
	TArray<FSpawnInfo> SpawnInfoArray;
};

class CardEventBattle
{
public : 
	void Parse(const FXmlNode* Node);

	TArray<FBattleInfo> m_BattleInfo;
};

//������ CardActor���� ������ �ִ� �̺�Ʈ�� ������ �� ó���� ����ϴ� Ŭ����
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
	void SetBattleInfo(CardEventBattle& battle) { m_Battle = battle; }
	
	int32 GetID() { return m_Id; }
	FString GetTitle() { return m_Title; }
	CardEventDialog& GetDialog(int32 index) { return m_Dialogs[index]; }
	FResult& GetEventResult(int32 id) { return m_Result.m_Results[id - 1]; }
	FReward& GetEventReward(int32 id) { return m_Reward.m_Rewards[id - 1]; }
	FBattleInfo& GetEventBattle(int32 id) { return m_Battle.m_BattleInfo[id - 1]; }

	int32 GetNextDialog(int32 index) { return m_Dialogs[index].m_Next; }
	int32 GetDialogEventResult(int32 index) { return m_Dialogs[index].m_Text.Result; }

private : 
	int32 m_Id;
	FString m_Title;
	TMap<int32, CardEventDialog> m_Dialogs;
	CardEventResult m_Result;
	CardEventReward m_Reward;
	CardEventBattle m_Battle;
};

class CardEventResource
{
public : 
	void Parse(const FString dir);

	static CardEventResource* GetInstance()
	{
		// TODO : Need to change it to double-checking locking in multi-thread environment.  
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