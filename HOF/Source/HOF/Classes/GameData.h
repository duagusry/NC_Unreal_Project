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

namespace EGameKey
{
	enum Type
	{
		Tap, 
		Hold, 
	};

	enum Event
	{
		IE_Pressed = 0, 
		IE_Released = 1,
		IE_Repeat = 2, 
		IE_DoubleClick = 3, 
		IE_Axis = 4, 
		IE_Max = 5, 
	};

}


USTRUCT()
struct FGameData
{
	GENERATED_BODY()
};