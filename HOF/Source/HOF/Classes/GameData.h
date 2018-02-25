#pragma once

#include "GameData.generated.h"

namespace EGameplayState
{
	enum Type
	{
		Init, 
		Menu,
		Setting,
		World,
		Battle,
		Finished,
	};
}


USTRUCT()
struct FGameData
{
	GENERATED_BODY()
};