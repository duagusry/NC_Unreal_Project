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

namespace SizeInGame
{
	static const short WORLD_SLOT_WIDTH = 8;
	static const short WORLD_SLOT_HEIGHT = 8;

	static const float WORLD_WIDTH = 1600.0f;
	static const float WORLD_HEIGHT = 2400.0f;

	static const float CARD_WIDTH = 160.0f;
	static const float CARD_HEIGHT = 240.0f;

	static const float BOARD_BASE_LOC_X = 0.0f;
	static const float BOARD_BASE_LOC_Y = 0.0f;

	static const float WIDGET_POSITION_X = 200.0f;
	static const float WIDGET_POSITION_Y = 70.0f;

	static const float WIDGET_SIZE_X = 1200.0f;
	static const float WIDGET_SIZE_Y = 50.0f;
}

namespace NumberInGame
{
	static const int MAX_SELECTION_COUNT = 4;
}

USTRUCT()
struct FGameData
{
	GENERATED_BODY()
};