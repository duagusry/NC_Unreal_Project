// Fill out your copyright notice in the Description page of Project Settings.

#include "XmlConverter.h"
#include "UnrealType.h"
#include "XmlParser.h"

template<typename T>
TArray<T*> XmlConverter::ToList(const FXmlNode *root)
{
	TArray<T*> ItemList;

	for (const auto &ListNode : root->GetChildrenNodes())
		ItemList.Add(ConvertRow<T>(ListNode));

	return ItemList;
}

template<typename T>
T* XmlConverter::ConvertRow(const FXmlNode *root)
{
	T *NewObj = NewObject<T>(); // T의 생성자가 noparam이어야해 

	for (const auto &ChildNode : root->GetChildrenNodes())
	{
		for (TFieldIterator<UProperty> PropIt(NewObj->GetClass()); PropIt; ++PropIt)
		{
			UProperty *Property = *PropIt;

			if (ChildNode->GetTag().Equals(Property->GetName()))
			{
				auto ValuePtr = Property->ContainerPtrToValuePtr<void>(NewObj);

				if (auto *IntProperty = Cast<UIntProperty>(Property))
				{
					IntProperty->SetIntPropertyValue(ValuePtr, FCString::Atoi64(*(ChildNode->GetContent())));
				}
				else if (auto *FloatProperty = Cast<UFloatProperty>(Property))
				{
					FloatProperty->SetFloatingPointPropertyValue(ValuePtr, FCString::Atof(*(ChildNode->GetContent())));
				}
				else if (auto *StrProperty = Cast<UStrProperty>(Property))
				{
					StrProperty->SetPropertyValue(ValuePtr, ChildNode->GetContent());
				}
				else if (auto *NameProperty = Cast<UNameProperty>(Property))
				{
					NameProperty->SetPropertyValue(ValuePtr, FName(*(ChildNode->GetContent())));
				}
				else if (auto *BoolProperty = Cast<UBoolProperty>(Property))
				{
					BoolProperty->SetPropertyValue(ValuePtr, ChildNode->GetContent() == "true" ? true : false);
				}
				else if (auto *EnumProperty = Cast<UEnumProperty>(Property))
				{
					EnumProperty->GetUnderlyingProperty()->SetIntPropertyValue(ValuePtr, FCString::Atoi64(*(ChildNode->GetContent())));
				}
			}
		}
	}

	return NewObj;
}