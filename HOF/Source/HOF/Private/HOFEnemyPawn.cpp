// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFEnemyPawn.h"
#include "HOF.h"
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

	PawnSenses = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSenses"));
	PawnSenses->SightRadius = 1000.0f;
	PawnSenses->bOnlySensePlayers = true;
	PawnSenses->bHearNoises = false;
	PawnSenses->OnSeePawn.AddDynamic(this, &AHOFEnemyPawn::OnSeePlayer);

	FName BTPath = TEXT("BehaviorTree'/Game/AI/EnemyBT.EnemyBT'"); 
	behaviorTreeAsset = Cast<UBehaviorTree>(StaticLoadObject(UBehaviorTree::StaticClass(), NULL, *BTPath.ToString()));
	AIControllerClass = AHOFEnemyController::StaticClass();

	enemyState = CreateDefaultSubobject<AHOFPlayerState>(TEXT("EnemyPlayerState"));
	AB_LOG(Warning, TEXT("Create EnemyState"));
	MaxHP = CurrentHP = 100.0f;
	isDead = false;
}

// Called when the game starts or when spawned
void AHOFEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void AHOFEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AHOFEnemyPawn::TakeDamage(float Damage, const FDamageEvent &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (CurrentHP <= 0.f)
		return 0.f;

	if (ActualDamage > 0.f)
	{
		CurrentHP = FMath::Clamp(CurrentHP - ActualDamage, 0.0f, MaxHP);
		AB_LOG(Warning, TEXT("HP:%f"), CurrentHP);

		if (CurrentHP <= 0)
			SetCurrentState(EHOFCharacterState::DEAD);//isDead = true;
	}
	return ActualDamage;
}

bool AHOFEnemyPawn::IsRunning()
{
	if(FloatPawnMovement->Velocity.Size() > 0)
		return true;
	else
		return false;
}

bool AHOFEnemyPawn::IsDead()
{
	return isDead;
}

AHOFPlayerState * AHOFEnemyPawn::GetEnemyState()
{
	if(!enemyState)
		enemyState = NewObject<AHOFPlayerState>();

	return enemyState;
}

void AHOFEnemyPawn::OnSeePlayer(APawn * InPawn)
{
	SetCurrentState(EHOFCharacterState::CHASE);
	Instigator = InPawn;
}

void AHOFEnemyPawn::SetCurrentState(EHOFCharacterState newState)
{
	if (GetEnemyState()->GetState() != EHOFCharacterState::DEAD)
	{
		Cast<AHOFEnemyController>(GetController())->SetStateInBlackBoard(newState);
		GetEnemyState()->SetState(newState);
	}
}