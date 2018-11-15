#include "HOFItemResource.h"
#include "HOFItem.h"
#include "XmlParser.h"
#include "XmlConverter.h"
#include "HOFWeaponItem.h"

void UItemResource::Parse(const FString dir)
{
	const FXmlFile File(dir);
	const FXmlNode *WeaponListNodes = File.GetRootNode();
	const auto &WeaponItemList = XmlConverter::ToList<AHOFWeaponItem>(WeaponListNodes);

	for (const auto &WeaponItem : WeaponItemList)
		ItemMap.Add(WeaponItem->Id, WeaponItem);
}

AHOFItem* UItemResource::GetItemFromId(int32 id)
{
	auto item = ItemMap.Find(id);
	return *item;
}
