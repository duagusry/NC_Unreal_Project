// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyResources.h"
#include "HOF.h"
#include "Engine/ObjectLibrary.h"
#include "Engine/World.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "HOFEnemyPawn.h"

TMap<FString, TSubclassOf<AHOFEnemyPawn>> EnemyResources::PawnByName;

void EnemyResources::Init()
{
	InitSpecyMap();
}

bool EnemyResources::Contains(FString enemyType)
{
	return EnemyResources::PawnByName.Contains(enemyType);
}

TSubclassOf<AHOFEnemyPawn> EnemyResources::GetSubClassOf(FString enemyType)
{
	return EnemyResources::PawnByName[enemyType];
}

void EnemyResources::InitSpecyMap()
{
	auto assets = LoadEnemyBlueprintAssets();

	for (auto asset : *assets)
		ExtractEnemyNameAndStoreWithAsset(asset);
}

TSharedPtr<TArray<UBlueprintGeneratedClass*>> EnemyResources::LoadEnemyBlueprintAssets()
{
	auto ObjectLibrary = UObjectLibrary::CreateLibrary(AActor::StaticClass(), true, true);
	ObjectLibrary->AddToRoot();
	ObjectLibrary->LoadBlueprintsFromPath(TEXT("/Game/Blueprints/Enemy"));
	//AB_LOG(Warning, TEXT("Assets: %d"), numOfAssets);

	auto blueprintAssets = MakeShared<TArray<UBlueprintGeneratedClass*>>();
	ObjectLibrary->GetObjects(*blueprintAssets);

	AB_LOG(Warning, TEXT("Found maps: %d"), blueprintAssets->Num());
	return blueprintAssets;
}

void EnemyResources::ExtractEnemyNameAndStoreWithAsset(UBlueprintGeneratedClass *asset)
{
	auto assetName = asset->GetName();
	if (!IsValidName(assetName)) return;
	auto enemyName = GetEnemyName(assetName);

	UBlueprint* MyBP = Cast<UBlueprint>(asset->ClassGeneratedBy);
	TSubclassOf<AHOFEnemyPawn> enemyPawn= CastChecked<UClass>(MyBP->GeneratedClass);

	PawnByName.Add(enemyName, enemyPawn);
}

bool EnemyResources::IsValidName(FString name)
{
	if (name.StartsWith(TEXT("SKEL_"))) return false;

	return true;
}

FString EnemyResources::GetEnemyName(FString originalName)
{
	TArray<FString> token;
	const TCHAR *delim = TEXT("_");
	originalName.ParseIntoArray(token, TEXT("_"), true);
	return token[1]; // BP_LOGUE -> LOGUE
}



