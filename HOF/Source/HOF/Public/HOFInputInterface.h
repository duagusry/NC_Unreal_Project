#pragma once

#include "Interface.h"
#include "HOFInputInterface.generated.h"

/** Interface for actors which can be selected */
UINTERFACE()
class UHOFInputInterface : public UInterface
{
	GENERATED_BODY()
};

class IHOFInputInterface
{
	GENERATED_BODY()

public : 

	UFUNCTION(BlueprintNativeEvent)
	void OnInputTap();
};