// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFEnemyController.h"
#include "HOF.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "AI/Navigation/NavigationSystem.h"
#include "HOFEnemyPawn.h"

AHOFEnemyController::AHOFEnemyController(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));
	BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	HomeLocKey = "HomeLocation";
	IdleTimeKey = "IdleTime";
	TargetLocKey = "TargetLocation";
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
		AB_LOG(Warning, TEXT("In MyPawn"));
		BlackboardComp->InitializeBlackboard(*(pawn->behaviorTreeAsset->BlackboardAsset));

		int32 homeLocKeyID = BlackboardComp->GetKeyID("HomeLocation");
		int32 idleTimeKeyID = BlackboardComp->GetKeyID("IdleTime");

		BlackboardComp->SetValueAsVector(HomeLocKey, pawn->GetActorLocation());
		BlackboardComp->SetValueAsFloat(IdleTimeKey, 2);
		FNavLocation targetLoc;
		UNavigationSystem::GetCurrent(GetWorld())->GetRandomPointInNavigableRadius(pawn->GetActorLocation(), 1000, targetLoc);
		BlackboardComp->SetValueAsVector(TargetLocKey, targetLoc.Location);

		BehaviorComp->StartTree(*(pawn->behaviorTreeAsset));
	}
}

