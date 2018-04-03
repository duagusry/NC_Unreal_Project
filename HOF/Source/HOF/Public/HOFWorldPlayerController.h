// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HOFWorldInput.h"
#include "HOFWorldPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HOF_API AHOFWorldPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public : 
	AHOFWorldPlayerController();

protected : 
	//실제 인풋을 처리하는 부분
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void SetupInputComponent() override;
	
	//Input Handlers
	void OnTapPressed(const FVector2D& ScreenPosition, float DownTime);

	AActor* GetClickedActor(const FVector2D& ScreenPoint, FVector& WorldPoint);
	void SetSelectedActor(AActor* NewSelectedActor, const FVector& NewPosition);

	/** Custom input handler. */
	UPROPERTY()
	class UHOFWorldInput* InputHandler;

	/** currently selected actor */
	TWeakObjectPtr<AActor> SelectedActor;

};
