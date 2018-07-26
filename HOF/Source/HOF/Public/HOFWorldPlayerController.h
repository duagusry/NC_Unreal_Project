// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HOFWorldInput.h"
#include "HOFWorldCardActor.h"
#include "HOFGameState.h"
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

	virtual void BeginPlay() override;

	void ShowEventWidget(int32 id, AHOFWorldCardActor* pCard, int32 returnDialog = 1);

protected : 
	//실제 인풋을 처리하는 부분
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void SetupInputComponent() override;
	
	//Input Handlers
	void OnTapPressed(const FVector2D& ScreenPosition, float DownTime);

	AActor* GetClickedActor(const FVector2D& ScreenPoint, FVector& WorldPoint);
	void SetSelectedActor(AActor* NewSelectedActor, const FVector& NewPosition);

	bool CanProcessWorldInput();

	/** Custom input handler. */
	UPROPERTY()
	class UHOFWorldInput* InputHandler;

	/** currently selected actor */
	TWeakObjectPtr<AActor> SelectedActor;
	
	//위젯은 삭제나 파괴가 불가능함.
	//따라서 위젯을 여러개 만들어놓으면 메모리에 큰 영향을 줄 수 있음.
	//위젯은 가급적 하나 만든걸 재사용하는게 좋음

	// The class that will be used for the players Inventory UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player, HUD and UI")
	TSubclassOf<class UHOFTextWidget> BP_EventWidget;

	// The instance of the players Inventory UI Widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player, HUD and UI")
	class UHOFTextWidget* EventWidget;
	
	AHOFGameState* GameState;
};
