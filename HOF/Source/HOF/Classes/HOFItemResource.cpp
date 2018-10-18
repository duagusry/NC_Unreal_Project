#include "HOFItemResource.h"
#include "HOFItem.h"
#include "XmlParser.h"

ItemResource* ItemResource::ItemResourceInstance = nullptr;

void ItemResource::Parse(const FString dir)
{
	const FXmlFile File(dir);
}

TSharedPtr<AHOFItem> ItemResource::GetItemFromId(int32 id)
{
	auto item = ItemMap.Find(id);

	return *item;
}
