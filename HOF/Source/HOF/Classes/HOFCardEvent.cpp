#include "HOFCardEvent.h"
#include "XmlParser.h"

CardEventResource* CardEventResource::CardEventResourceInstance = nullptr;

void CardEventResource::Parse(const FString dir)
{
	const FXmlFile file(dir);

	const FXmlNode* cardEventListNode = file.GetRootNode();
	const TArray<FXmlNode*> cardEventsNode = cardEventListNode->GetChildrenNodes();

	for (auto eventNode : cardEventsNode)
	{
		HOFCardEvent newCardEvent;
		newCardEvent.SetID(FCString::Atoi(*(eventNode->GetAttribute(FString("id")))));

		CardEventDialog newDialog;
		CardEventResult newResult;
		CardEventReward newReward;

		const TArray<FXmlNode*> cardEventsItemNode = eventNode->GetChildrenNodes();

		for (auto itemNode : cardEventsItemNode)
		{
			if (itemNode->GetTag().Equals(FString("Dialog")))
			{
				newDialog.Parse(itemNode);
				newCardEvent.SetDialog(newDialog);
			}
			else if (itemNode->GetTag().Equals(FString("Result")))
			{
				newResult.Parse(itemNode);
				newCardEvent.SetResult(newResult);
			}
			else if (itemNode->GetTag().Equals(FString("Reward")))
			{
				newReward.Parse(itemNode);
				newCardEvent.SetReward(newReward);
			}
		}

		m_Map.Add(newCardEvent.GetID(), newCardEvent);
	}
}

const HOFCardEvent CardEventResource::GetCardEventFromId(int32 id)
{
	return g_CardEvent->m_Map.FindOrAdd(id);
}

HOFCardEvent::HOFCardEvent(const HOFCardEvent& other)
	: m_Id(other.m_Id), 
	m_Dialog(other.m_Dialog), 
	m_Result(other.m_Result), 
	m_Reward(other.m_Reward)
{ }

void CardEventDialog::Parse(const FXmlNode * Node)
{
	const TArray<FXmlNode*> dialogEventList = Node->GetChildrenNodes();

	for (auto node : dialogEventList)
	{
		if (node->GetTag().Equals(FString("Text")))
		{
			m_Texts.Add(node->GetContent());
		}
		else if (node->GetTag().Equals(FString("SelectionText")))
		{
			FSelectionText newText;
			newText.Result = FCString::Atoi(*(node->GetAttribute(FString("result"))));
			newText.Text = node->GetContent();

			m_SelectionTexts.Add(newText);
		}
	}
}

void CardEventResult::Parse(const FXmlNode * Node)
{
	const TArray<FXmlNode*> ResultEventList = Node->GetChildrenNodes();

	for (auto node : ResultEventList)
	{
		FResult newResult;
		newResult.Id = FCString::Atoi(*(node->GetAttribute(FString("id"))));
		newResult.Reward = FCString::Atoi(*(node->GetAttribute(FString("reward"))));
		newResult.Event = FCString::Atoi(*(node->GetAttribute(FString("event"))));
		newResult.Transfer = node->GetAttribute(FString("transfer")).Equals(FString("true")) ? true : false;
		newResult.Gambit = node->GetAttribute(FString("gambit")).Equals(FString("true")) ? true : false;

		m_Results.Add(newResult);
	}
}

void CardEventReward::Parse(const FXmlNode * Node)
{
	const TArray<FXmlNode*> RewardEventList = Node->GetChildrenNodes();

	for (auto node : RewardEventList)
	{
		FReward newReward;
		newReward.Id = FCString::Atoi(*(node->GetAttribute(FString("id"))));

		const TArray<FXmlNode*> eventList = node->GetChildrenNodes();

		for (auto node : eventList)
		{
			if (node->GetTag().Equals(FString("Item")))
			{
				FItem newItem;
				newItem.Id = FCString::Atoi(*(node->GetAttribute(FString("id"))));
				newItem.Amount = FCString::Atoi(*(node->GetAttribute(FString("amount"))));

				newReward.ItemList.Add(newItem);
			}
			else if (node->GetTag().Equals(FString("Food")))
			{
				newReward.Food = FCString::Atoi(*(node->GetAttribute(FString("amount"))));
			}
			else if (node->GetTag().Equals(FString("Gold")))
			{
				newReward.Gold = FCString::Atoi(*(node->GetAttribute(FString("amount"))));
			}
			else if (node->GetTag().Equals(FString("MaxHealth")))
			{
				newReward.MaxHealth = FCString::Atoi(*(node->GetAttribute(FString("amount"))));
			}
			else if (node->GetTag().Equals(FString("CurrentHealth")))
			{
				newReward.CurrentHealth = FCString::Atoi(*(node->GetAttribute(FString("amount"))));
			}
		}

		m_Rewards.Add(newReward);
	}
}
