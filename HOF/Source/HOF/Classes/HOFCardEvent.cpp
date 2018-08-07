#include "HOFCardEvent.h"
#include "XmlParser.h"

CardEventResource* CardEventResource::CardEventResourceInstance = nullptr;

void CardEventResource::Parse(const FString dir)
{
	const FXmlFile File(dir);

	const FXmlNode* CardEventListNode = File.GetRootNode();
	const TArray<FXmlNode*> CardEventsNode = CardEventListNode->GetChildrenNodes();

	for (const auto& EventNode : CardEventsNode)
	{
		HOFCardEvent NewCardEvent;
		NewCardEvent.SetID(FCString::Atoi(*(EventNode->GetAttribute(FString("id")))));

		CardEventResult NewResult{};
		CardEventReward NewReward{};
		CardEventBattle NewBattle{};

		const TArray<FXmlNode*> CardEventsItemNode = EventNode->GetChildrenNodes();

		for (const auto& ItemNode : CardEventsItemNode)
		{

			if (ItemNode->GetTag().Equals(FString("Title")))
			{
				NewCardEvent.SetTitle(ItemNode->GetContent());
			}
			else if (ItemNode->GetTag().Equals(FString("Dialog")))
			{
				CardEventDialog NewDialog{};

				NewDialog.Parse(ItemNode);
				NewCardEvent.AddDialog(NewDialog);
			}
			else if (ItemNode->GetTag().Equals(FString("Result")))
			{
				NewResult.Parse(ItemNode);
			}
			else if (ItemNode->GetTag().Equals(FString("Reward")))
			{
				NewReward.Parse(ItemNode);
			}
			else if (ItemNode->GetTag().Equals(FString("Battle")))
			{
				NewBattle.Parse(ItemNode);
			}
		}

		NewCardEvent.SetResult(NewResult);
		NewCardEvent.SetReward(NewReward);
		NewCardEvent.SetBattleInfo(NewBattle);
		CardEventMap.Add(NewCardEvent.GetID(), NewCardEvent);
	}
}

const HOFCardEvent CardEventResource::GetCardEventFromId(int32 id)
{
	return g_CardEvent->CardEventMap.FindOrAdd(id);
}

HOFCardEvent::HOFCardEvent(const HOFCardEvent& other)
	: Id(other.Id), 
	Title(other.Title), 
	Result(other.Result), 
	Reward(other.Reward), 
	Battle(other.Battle)
{
	DialogArray = other.DialogArray;
}

void CardEventDialog::Parse(const FXmlNode * Node)
{
	const TArray<FXmlNode*> DialogEventList = Node->GetChildrenNodes();

	Id = FCString::Atoi(*(Node->GetAttribute(FString("id"))));
	NextId = FCString::Atoi(*(Node->GetAttribute(FString("next"))));

	for (const auto& Node : DialogEventList)
	{
		if (Node->GetTag().Equals(FString("Text")))
		{
			FNormalText NewText{};
			NewText.Result = FCString::Atoi(*(Node->GetAttribute(FString("result"))));
			NewText.Text = Node->GetContent();

			Text = NewText;
		}
		else if (Node->GetTag().Equals(FString("SelectionText")))
		{
			FSelectionText NewText{};
			NewText.Result = FCString::Atoi(*(Node->GetAttribute(FString("result"))));
			NewText.Text = Node->GetContent();

			SelectionTextArray.Add(NewText);
		}
	}
}

void CardEventResult::Parse(const FXmlNode * Node)
{
	const TArray<FXmlNode*> ResultEventList = Node->GetChildrenNodes();

	for (const auto &Node : ResultEventList)
	{
		FResult NewResult{};
		
		NewResult.Id = FCString::Atoi(*(Node->GetAttribute(FString("id"))));
		NewResult.Reward = FCString::Atoi(*(Node->GetAttribute(FString("reward"))));
		NewResult.Dialog = FCString::Atoi(*(Node->GetAttribute(FString("dialog"))));
		NewResult.Gambit = Node->GetAttribute(FString("gambit")).Equals(FString("true")) ? true : false;

		ResultArray.Add(NewResult);
	}
}

bool CardEventResult::IsChildNodeName(const FXmlNode *node, FString tagName)
{
	return node->GetTag().Equals(tagName);
}

FString CardEventResult::GetAttribute(FXmlNode *node, FString attrName)
{
	return node->GetAttribute(attrName);
}

void CardEventReward::Parse(const FXmlNode * Node)
{
	const TArray<FXmlNode*> RewardEventList = Node->GetChildrenNodes();

	for (const auto& Node : RewardEventList)
	{
		FReward NewReward{};
		NewReward.Id = FCString::Atoi(*(Node->GetAttribute(FString("id"))));

		const TArray<FXmlNode*> EventList = Node->GetChildrenNodes();

		for (const auto& Node : EventList)
		{
			if (Node->GetTag().Equals(FString("Item")))
			{
				FItem NewItem;
				NewItem.Id = FCString::Atoi(*(Node->GetAttribute(FString("id"))));
				NewItem.Amount = FCString::Atoi(*(Node->GetAttribute(FString("amount"))));

				NewReward.ItemArray.Add(NewItem);
			}
			else if (Node->GetTag().Equals(FString("Food")))
			{
				NewReward.Food = FCString::Atoi(*(Node->GetAttribute(FString("amount"))));
			}
			else if (Node->GetTag().Equals(FString("Gold")))
			{
				NewReward.Gold = FCString::Atoi(*(Node->GetAttribute(FString("amount"))));
			}
			else if (Node->GetTag().Equals(FString("MaxHealth")))
			{
				NewReward.MaxHealth = FCString::Atoi(*(Node->GetAttribute(FString("amount"))));
			}
			else if (Node->GetTag().Equals(FString("CurrentHealth")))
			{
				NewReward.CurrentHealth = FCString::Atoi(*(Node->GetAttribute(FString("amount"))));
			}
			else if (Node->GetTag().Equals(FString("Reveal")))
			{
				NewReward.Reveal = FCString::Atoi(*(Node->GetAttribute(FString("amount"))));
			}
			else if (Node->GetTag().Equals(FString("Battle")))
			{
				NewReward.Battle = FCString::Atoi(*(Node->GetAttribute(FString("id"))));
			}
		}

		RewardArray.Add(NewReward);
	}
}

void CardEventBattle::Parse(const FXmlNode * Node)
{
	const TArray<FXmlNode*> BattleEventList = Node->GetChildrenNodes();

	for (const auto& Node : BattleEventList)
	{
		FBattleInfo NewBattle;

		NewBattle.Id = FCString::Atoi(*(Node->GetAttribute(FString("id"))));
		NewBattle.ReturnDialog = FCString::Atoi(*(Node->GetAttribute(FString("returnDialog"))));

		const TArray<FXmlNode*> SpawnList = Node->GetChildrenNodes();
		for (const auto& Node : SpawnList)
		{
			if (Node->GetTag().Equals(FString("Spawn")))
			{
				FSpawnInfo NewSpawn;
				NewSpawn.Type = Node->GetAttribute(FString("type"));
				NewSpawn.Amount = FCString::Atoi(*(Node->GetAttribute(FString("amount"))));

				NewBattle.SpawnInfoArray.Add(NewSpawn);
			}
		}

		BattleInfoArray.Add(NewBattle);
	}
}
