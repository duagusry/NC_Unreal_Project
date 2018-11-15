#pragma once

#include "CoreMinimal.h"
#include "XmlParser.h"
#include "HOFItemResource.generated.h"

class AHOFItem;

UCLASS()
class HOF_API UItemResource : public UObject
{
	GENERATED_BODY()

public:
	AHOFItem* GetItemFromId(int32 id);
	void Parse(const FString dir);

private:
	UPROPERTY()
	TMap<int32, AHOFItem*> ItemMap;
};


