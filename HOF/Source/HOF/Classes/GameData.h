#pragma once

#include "GameData.generated.h"

class AHOFWorldCardActor;

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

	static const float REAL_SLOT_SIZE_X = WORLD_HEIGHT / WORLD_SLOT_HEIGHT;
	static const float REAL_SLOT_SIZE_Y = WORLD_WIDTH / WORLD_SLOT_WIDTH;
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

	struct WorldStatusData
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

		WorldStatusData() = default;
		
		WorldStatusData& operator=(const WorldStatusData& ref)
		{
			WorldBoardData = ref.WorldBoardData;
			CurrentPosition = ref.CurrentPosition;
			CurrentDialogId = ref.CurrentDialogId;

			return *this;
		}
	};

	template <typename T>
	class Stat
	{
	public : 
		Stat(T current, T max, T min)
			: CurrentValue(current)
			, MaxValue(max)
			, MinValue(min)
		{ }

		Stat(const Stat& ref) = default;
		Stat& operator=(const Stat& ref) = default;

		inline void operator()(T value) { value > 0 ? Ceil(value) : Floor(value); }	// Modify Current Value

		inline void ModifyMaxValue(T value) { MaxValue = MaxValue + value <= MinValue ? MinValue : MaxValue + value; }
		inline void ModifyMinValue(T value) { MinValue = MinValue + value >= MaxValue ? MaxValue : MinValue + value; }

		inline bool CheckOnMinValue() { return CurrentValue <= MinValue; }

		inline const T GetCurrentValue() const { return CurrentValue; }
		// for logging
		inline const T GetMaxValue() const { return MaxValue; }
		inline const T GetMinValue() const { return MinValue; }

	private : 
		inline void Ceil(T value) { CurrentValue = CurrentValue + value >= MaxValue ? MaxValue : CurrentValue + value; }
		inline void Floor(T value) { CurrentValue = CurrentValue + value <= MinValue ? MinValue : CurrentValue + value; }

	private : 
		T CurrentValue;
		T MinValue;
		T MaxValue;
	};

	struct PlayerData
	{
		Stat<float> HP{ 100, 100, 0 };
		Stat<int32> Food{ 30, 100, 0 };
		Stat<int32> Gold{ 50, 1000, 0 };
		bool Alive;
	};

	struct BattleData
	{
		TMap<FString, int32> SpawnInfo;

		void Reset()
		{
			SpawnInfo.Reset();
		}
	};
}

USTRUCT()
struct FGameData
{
	GENERATED_BODY()
};