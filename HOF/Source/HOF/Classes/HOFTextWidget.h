#pragma once

#include "UMG.h"
#include "HOFTextWidget.generated.h"


UCLASS()
class UHOFTextWidget : public UUserWidget
{
public:
	GENERATED_BODY()
		
private : 

	UPROPERTY()
	TArray<UTextBlock*> Text;

	UPROPERTY()
	TArray<UButton*> SelectText;
};