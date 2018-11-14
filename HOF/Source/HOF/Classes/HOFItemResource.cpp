#include "HOFItemResource.h"
#include "HOFItem.h"
#include "XmlParser.h"
#include "XmlConverter.h"
#include "HOFWeaponItem.h"

ItemResource* ItemResource::ItemResourceInstance = nullptr;

ItemResource::ItemResource()
{
	Parse("D:\\HandOfFate2\\HOF\\Resource\\Xml\\WeaponItem.xml");
}

void ItemResource::Parse(const FString dir)
{
	const FXmlFile File(dir);
	const FXmlNode *WeaponListNodes = File.GetRootNode();
	const auto &WeaponItemList = XmlConverter::ToList<AHOFWeaponItem>(WeaponListNodes);

	for (const auto &WeaponItem : WeaponItemList)
		ItemMap.Add(WeaponItem->Id, WeaponItem);
}

AHOFItem* ItemResource::GetItemFromId(int32 id)
{
	auto item = ItemMap.Find(id);
	return *item;
}
