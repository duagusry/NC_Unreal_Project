#pragma once

#include "XmlParser.h"

class AHOFItem;

class ItemResource
{
public:
	void Parse(const FString dir);

	static ItemResource* GetInstance()
	{
		// TODO : Need to change it to double-checking locking in multi-thread environment.  
		if (!ItemResourceInstance)
			ItemResourceInstance = new ItemResource();

		return ItemResourceInstance;
	}

	TSharedPtr<AHOFItem> GetItemFromId(int32 id);
	
private:
	ItemResource() { }

	TMap<int32, TSharedPtr<AHOFItem>> ItemMap;

	static ItemResource* ItemResourceInstance;
};


#define g_ItemResource ItemResource::GetInstance()

