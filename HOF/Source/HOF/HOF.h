// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(HOFGamePlay, Log, All);


#define AB_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

#define AB_LOG_CALLONLY(Verbose) UE_LOG(HOFGamePlay, Verbose, TEXT("%s"), *AB_LOG_CALLINFO)

#define AB_LOG(Verbose, Format, ...) UE_LOG(HOFGamePlay, Verbose, TEXT("%s%s"), *AB_LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))