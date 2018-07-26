#pragma once

#include "GameData.generated.h"

class AHOFWorldCardActor;

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
	static const short WORLD_SLOT_WIDTH = 3;
	static const short WORLD_SLOT_HEIGHT = 3;

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
	static const int TEXT_BLOCK_START = 2;

	static const int32 FoodConsumption = 1;
	static const int32 HealByFood = 8;
	static const int32 DamageByFood = 20;
}

namespace BaseStructs
{
	struct Position
	{
		int32 x;
		int32 y;
	};

	struct TransferData
	{
		struct WorldSlotDataStruct
		{
			int32 EventId;
			bool IsVisited;
			bool IsRevealed;
		};

		struct WorldBoardDataStruct
		{
			TArray<WorldSlotDataStruct> WorldSlotData;
			TArray<int32> InitialEventArray;
		} WorldBoardData;

		Position CurrentPosition;
		int32 CurrentDialogId;
		bool IsSet;

		TransferData() = default;
		
		TransferData& operator=(const TransferData& ref)
		{
			WorldBoardData = ref.WorldBoardData;
			CurrentPosition = ref.CurrentPosition;
			CurrentDialogId = ref.CurrentDialogId;

			return *this;
		}
	};

	struct PlayerData
	{
		float MaxHP;
		float CurrentHP;
		int32 Food;
		int32 Gold;
		bool Alive;
	};
}

USTRUCT()
struct FGameData
{
	GENERATED_BODY()
};