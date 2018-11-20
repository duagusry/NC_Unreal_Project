#include "HOFItemResource.h"
#include "HOFItem.h"
#include "XmlParser.h"
#include "XmlConverter.h"
#include "DynamicObjectLoader.h"
#include "HOFWeaponItem.h"

void UItemResource::Parse(const FString dir)
{
	const FXmlFile File(dir);
	const FXmlNode *WeaponListNodes = File.GetRootNode();
	const auto &WeaponItemList = XmlConverter::ToList<AHOFWeaponItem>(WeaponListNodes);

	for (const auto &WeaponItem : WeaponItemList)
		ItemMap.Add(WeaponItem->Id, WeaponItem);

	GetMeshResource();
}

AHOFItem* UItemResource::GetItemFromId(int32 id)
{
	auto item = ItemMap.Find(id);
	return *item;
}

void UItemResource::GetMeshResource()
{
	for (const auto &Each : ItemMap)
		Each.Value->Mesh = DynamicObjectLoader::Load<USkeletalMesh>(Each.Value->AssetPath);
}
