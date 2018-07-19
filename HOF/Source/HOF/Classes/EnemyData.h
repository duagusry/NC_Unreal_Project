// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData.h"
/**
 * 
 */

class UBlueprintGeneratedClass;
class AHOFEnemyPawn;
struct FAssetData;

class HOF_API EnemyData
{
private:
	const FString ENEMY_BLUEPRINT_PATH = TEXT("/Game/Blueprints/Enemy");

public:
	EnemyData();
	~EnemyData();

	void SetEnemyData(FString enemySpecyStr, int number);

	TSubclassOf<AHOFEnemyPawn> enemySpecy;
	int number;

private:
	void InitSpecyMap();
	void ExtractEnemyNameAndStoreWithAsset(UBlueprintGeneratedClass * asset);
	bool IsValidName(FString name);
	TSharedPtr<TArray<UBlueprintGeneratedClass*>> LoadEnemyBlueprintAssets();
	FString GetEnemyName(FString originalName);

	TMap<FString, TSubclassOf<AHOFEnemyPawn>> PawnByName;
};
