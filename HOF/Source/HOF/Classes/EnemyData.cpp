// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyData.h"
#include "HOF.h"
#include "Engine/ObjectLibrary.h"
#include "Engine/World.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "HOFEnemyPawn.h"

EnemyData::EnemyData()
{
	InitSpecyMap();
}

EnemyData::~EnemyData()
{
}

void EnemyData::SetEnemyData(FString enemySpecyStr, int number)
{
	enemySpecy = specyMap[enemySpecyStr];
	this->number = number;
}

void EnemyData::InitSpecyMap()
{
	auto assets = LoadEnemyBlueprintAssets();

	for (auto asset : *assets)
		ExtractEnemyNameAndStoreWithAsset(asset);
}

void EnemyData::ExtractEnemyNameAndStoreWithAsset(UBlueprintGeneratedClass *asset)
{
	auto assetName = asset->GetName();
	if (!IsValidName(assetName)) return;
	auto enemyName = GetEnemyName(assetName);

	specyMap.Add(enemyName, asset->GetDefaultObject()->GetClass());
}

bool EnemyData::IsValidName(FString name)
{
	if (name.StartsWith(TEXT("SKEL_"))) return false;

	return true;
}

TSharedPtr<TArray<UBlueprintGeneratedClass*>> EnemyData::LoadEnemyBlueprintAssets()
{
	auto ObjectLibrary = UObjectLibrary::CreateLibrary(AActor::StaticClass(), true, true);
	ObjectLibrary->AddToRoot();
	ObjectLibrary->LoadBlueprintsFromPath(ENEMY_BLUEPRINT_PATH);
	//AB_LOG(Warning, TEXT("Assets: %d"), numOfAssets);

	auto blueprintAssets = MakeShared<TArray<UBlueprintGeneratedClass*>>();
	ObjectLibrary->GetObjects(*blueprintAssets);

	AB_LOG(Warning, TEXT("Found maps: %d"), blueprintAssets->Num());
	return blueprintAssets;
}

FString EnemyData::GetEnemyName(FString originalName)
{
	TArray<FString> token;
	const TCHAR *delim = TEXT("_");
	originalName.ParseIntoArray(token, TEXT("_"), true);
	return token[1]; // BP_LOGUE -> LOGUE
}



