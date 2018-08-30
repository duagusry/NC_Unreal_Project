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

class HOF_API EnemyResources
{
public:
	static void Init();
	static bool Contains(FString enemyType);
	static TSubclassOf<AHOFEnemyPawn> GetSubClassOf(FString enemyType);

private:
	static void InitSpecyMap();
	static void ExtractEnemyNameAndStoreWithAsset(UBlueprintGeneratedClass * asset);
	static bool IsValidName(FString name);
	static TSharedPtr<TArray<UBlueprintGeneratedClass*>> LoadEnemyBlueprintAssets();
	static FString GetEnemyName(FString originalName);

private:
	static TMap<FString, TSubclassOf<AHOFEnemyPawn>> PawnByName;
};
