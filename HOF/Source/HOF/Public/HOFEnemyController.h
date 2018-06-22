// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HOFEnemyController.generated.h"

/**
*
*/

enum EHOFCharacterState;

UCLASS()
class HOF_API AHOFEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AHOFEnemyController(const class FObjectInitializer& ObjectInitializer);

	virtual void Possess(APawn* InPawn) override;

	void SetStateInBlackBoard(EHOFCharacterState newState);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(transient)
		class UBlackboardComponent* BlackboardComp;

	UPROPERTY(transient)
		class UBehaviorTreeComponent* BehaviorComp;

	FName HomeLocKey;
	FName TargetLocKey;
	FName IdleTimeKey;
	FName StateKey;
};
