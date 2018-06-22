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

		CardEventResult newResult;
		CardEventReward newReward;

		const TArray<FXmlNode*> cardEventsItemNode = eventNode->GetChildrenNodes();

		for (auto itemNode : cardEventsItemNode)
		{

			if (itemNode->GetTag().Equals(FString("Title")))
			{
				newCardEvent.SetTitle(itemNode->GetContent());
			}
			else if (itemNode->GetTag().Equals(FString("Dialog")))
			{
				CardEventDialog newDialog;

				newDialog.Parse(itemNode);
				newCardEvent.AddDialog(newDialog);
			}
			else if (itemNode->GetTag().Equals(FString("Result")))
			{
				newResult.Parse(itemNode);
			}
			else if (itemNode->GetTag().Equals(FString("Reward")))
			{
				newReward.Parse(itemNode);
			}
		}

		newCardEvent.SetResult(newResult);
		newCardEvent.SetReward(newReward);
		m_Map.Add(newCardEvent.GetID(), newCardEvent);
	}
}

const HOFCardEvent CardEventResource::GetCardEventFromId(int32 id)
{
	return g_CardEvent->m_Map.FindOrAdd(id);
}

HOFCardEvent::HOFCardEvent(const HOFCardEvent& other)
	: m_Id(other.m_Id), 
	m_Title(other.m_Title), 
	m_Result(other.m_Result), 
	m_Reward(other.m_Reward)
{
	m_Dialogs = other.m_Dialogs;
}

void CardEventDialog::Parse(const FXmlNode * Node)
{
	const TArray<FXmlNode*> dialogEventList = Node->GetChildrenNodes();

	m_Id = FCString::Atoi(*(Node->GetAttribute(FString("id"))));
	m_Next = FCString::Atoi(*(Node->GetAttribute(FString("next"))));

	for (auto node : dialogEventList)
	{
		if (node->GetTag().Equals(FString("Text")))
		{
			FNormalText newText;
			newText.Result = FCString::Atoi(*(node->GetAttribute(FString("result"))));
			newText.Text = node->GetContent();

			m_Text = newText;
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
		newResult.Dialog = FCString::Atoi(*(node->GetAttribute(FString("dialog"))));
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
