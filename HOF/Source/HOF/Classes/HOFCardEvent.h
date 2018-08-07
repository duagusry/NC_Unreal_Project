#pragma once

#include "XmlParser.h"

struct FNormalText
{
	int32 Result;
	FString Text;
};

struct FSelectionText
{
	int32 Result;
	FString Text;
};

// Id, Next, FNormalText 한개, FSelectionText 다수
class CardEventDialog
{
public : 
	CardEventDialog() = default;
	void Parse(const FXmlNode* Node);
	
	int32 GetSelectionResult(int32 id) { return SelectionTextArray[id - 1].Result; }

	int32 Id;
	int32 NextId;
	FNormalText Text;
	TArray<FSelectionText> SelectionTextArray;
};

struct FResult
{
	bool HasMultiResult()
	{
		while (0)
		{
			if (Dialog > 0)
				break;

			if (Gambit)
				break;

			return false;
		}

		return true;
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


	TArray<FResult> ResultArray;

private:
	bool IsChildNodeName(const FXmlNode * node, FString tagName);
	FString GetAttribute(FXmlNode * node, FString attrName);
};

struct FItem
{
	int32 Id;
	int32 Amount;
};

struct FReward
{
	//이건 너무 많은데?
	// 비트플래그로 관리하는 것도 괜찮겠다.

	int32 Id;
	TArray<FItem> ItemArray;
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

	TArray<FReward> RewardArray;
};

struct FSpawnInfo
{
	FString Type;
	int32 Amount;
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

	TArray<FBattleInfo> BattleInfoArray;
};

//각각의 CardActor들이 가지고 있는 이벤트의 종류와 그 처리를 담당하는 클래스
class HOFCardEvent
{
public:
	HOFCardEvent() { }
	HOFCardEvent(const HOFCardEvent& other);

	void SetID(int32 id) { Id = id; }
	void SetTitle(FString title) { Title = title; }
	void AddDialog(CardEventDialog& dialog) { DialogArray.Add(dialog.Id, dialog); }
	void SetResult(CardEventResult& result) { Result = result; }
	void SetReward(CardEventReward& reward) { Reward = reward; }
	void SetBattleInfo(CardEventBattle& battle) { Battle = battle; }
	
	int32 GetID() { return Id; }
	FString GetTitle() { return Title; }
	CardEventDialog& GetDialog(int32 index) { return DialogArray[index]; }
	FResult& GetEventResult(int32 id) { return Result.ResultArray[id - 1]; }
	FReward& GetEventReward(int32 id) { return Reward.RewardArray[id - 1]; }
	FBattleInfo& GetEventBattle(int32 id) { return Battle.BattleInfoArray[id - 1]; }

	int32 GetNextDialog(int32 index) { return DialogArray[index].NextId; }
	int32 GetDialogEventResult(int32 index) { return DialogArray[index].Text.Result; }

private : 
	int32 Id;
	FString Title;
	TMap<int32, CardEventDialog> DialogArray;
	CardEventResult Result;
	CardEventReward Reward;
	CardEventBattle Battle;
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

		for (auto cardEvent : CardEventMap)
		{
			eventArray.Add(cardEvent.Key);
		}
	}

private : 
	TMap<int32, const HOFCardEvent> CardEventMap;

	CardEventResource() { }
	static CardEventResource* CardEventResourceInstance;
};


#define g_CardEvent CardEventResource::GetInstance()