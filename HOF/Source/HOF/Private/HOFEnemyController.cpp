// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFEnemyController.h"
#include "HOF.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "AI/Navigation/NavigationSystem.h"
#include "HOFPlayerState.h"
#include "HOFEnemyPawn.h"

AHOFEnemyController::AHOFEnemyController(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));
	BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	HomeLocKey = "HomeLocation";
	IdleTimeKey = "IdleTime";
	TargetLocKey = "TargetLocation";
	StateKey = "State";
}

void AHOFEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

void AHOFEnemyController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AHOFEnemyPawn* pawn = Cast<AHOFEnemyPawn>(InPawn);

	if (pawn && pawn->behaviorTreeAsset)
	{
		BlackboardComp->InitializeBlackboard(*(pawn->behaviorTreeAsset->BlackboardAsset));

		BlackboardComp->SetValueAsVector(HomeLocKey, pawn->GetActorLocation());
		BlackboardComp->SetValueAsFloat(IdleTimeKey, 2);
		FNavLocation targetLoc;
		UNavigationSystem::GetCurrent(GetWorld())->GetRandomPointInNavigableRadius(pawn->GetActorLocation(), 1000, targetLoc);
		BlackboardComp->SetValueAsVector(TargetLocKey, targetLoc.Location);

		BehaviorComp->StartTree(*(pawn->behaviorTreeAsset));
	}
}

void AHOFEnemyController::SetStateInBlackBoard(EHOFCharacterState newState)
{
	BlackboardComp->SetValueAsEnum(StateKey, newState);
}

