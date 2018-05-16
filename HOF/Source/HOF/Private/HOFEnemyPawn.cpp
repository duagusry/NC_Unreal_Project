// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFEnemyPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "HOFGameInstance.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/FloatingPawnMovement.h"
#include "HOFEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"

// Sets default values
AHOFEnemyPawn::AHOFEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = (UCapsuleComponent*)Capsule;
	Capsule->SetCapsuleSize(34.0f, 88.0f);

	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Capsule);
	Body->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Capsule);

	FloatPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawn"));

	FName BTPath = TEXT("BehaviorTree'/Game/AI/EnemyBT.EnemyBT'"); 
	behaviorTreeAsset = Cast<UBehaviorTree>(StaticLoadObject(UBehaviorTree::StaticClass(), NULL, *BTPath.ToString()));
	AIControllerClass = AHOFEnemyController::StaticClass();
}

// Called when the game starts or when spawned
void AHOFEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHOFEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHOFEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

