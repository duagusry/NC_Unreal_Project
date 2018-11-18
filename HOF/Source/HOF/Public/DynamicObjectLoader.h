// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class HOF_API DynamicObjectLoader
{
public:
	template <typename ObjClass>
	static FORCEINLINE ObjClass* Load(const FString& Path)
	{
		if (Path == "") return NULL;
		//~

		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path));
	}
};
