// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FXmlNode;

/**
 * 
 */
class HOF_API XmlConverter
{

public:
	template<typename T>
	static TArray<T*> ToList(const FXmlNode *root);

private:
	template<typename T>
	static T* ConvertRow(const FXmlNode *);
};
