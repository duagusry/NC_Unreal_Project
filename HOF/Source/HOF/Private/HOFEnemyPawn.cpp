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
#include "HOFBattleGameMode.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "HOFEnemyState.h"

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

	EnemyState = CreateDefaultSubobject<UHOFEnemyState>(TEXT("EnemyState"));
	AB_LOG(Warning, TEXT("Create EnemyState"));
	MaxHP = CurrentHP = 100.0f;
	Dead = false;
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
	const float& ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser); // ????

	if (ActualDamage > 0.f)
	{
		CurrentHP = FMath::Clamp(CurrentHP - ActualDamage, 0.0f, MaxHP);
		AB_LOG(Warning, TEXT("HP:%f"), CurrentHP);

		if (CurrentHP <= 0)
		{
			SetCurrentState(EHOFEnemyState::ENEMY_DEAD);
			const auto& gameMode = Cast<AHOFBattleGameMode>(GetWorld()->GetAuthGameMode());
			gameMode->OnEnemyDead();
		}
	}
	
	return ActualDamage;
}

void AHOFEnemyPawn::AttackHit()
{
	AB_LOG_CALLONLY(Warning);

	FHitResult HitResult(ForceInit);
	FVector StartPos = GetActorLocation();
	FVector EndPos = StartPos + GetActorForwardVector() * 100.0f;
	auto TraceParams = GetTraceParams();
	auto TraceObject = GetTraceObject(TArray<ECollisionChannel>{ECC_Pawn, ECC_WorldStatic});

	if (GetWorld()->SweepSingleByObjectType(HitResult, StartPos, EndPos, FQuat(), *TraceObject, FCollisionShape::MakeSphere(50.0f), *TraceParams))
		GiveDamage(HitResult);
}

TSharedPtr<FCollisionQueryParams> AHOFEnemyPawn::GetTraceParams()
{
	const FName TraceTag("MyTraceTag");
	GetWorld()->DebugDrawTraceTag = TraceTag;

	auto TraceParams = MakeShared<FCollisionQueryParams>(FName(TEXT("VictoreCore Trace")), true, this);
	TraceParams->bTraceComplex = true;
	TraceParams->bReturnPhysicalMaterial = false;
	TraceParams->TraceTag = TraceTag;

	//Ignore Actors
	TraceParams->AddIgnoredActor(this);
	return TraceParams;
}

TSharedPtr<FCollisionObjectQueryParams> AHOFEnemyPawn::GetTraceObject(const TArray<ECollisionChannel> &channels)
{
	auto TraceObject = MakeShared<FCollisionObjectQueryParams>();
	for (auto channel : channels)
		TraceObject->AddObjectTypesToQuery(channel);
	return TraceObject;
}

void AHOFEnemyPawn::GiveDamage(const FHitResult &HitResult)
{
	AB_LOG(Warning, TEXT("HitActor=%s"), *(HitResult.GetActor()->GetName()));
	float BaseDamage = 30.0f;

	FPointDamageEvent PointDamageEvent(BaseDamage, HitResult, GetActorForwardVector(), UDamageType::StaticClass());
	HitResult.GetActor()->TakeDamage(BaseDamage, PointDamageEvent, GetController(), this);
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
	return Dead;
}

UHOFEnemyState * AHOFEnemyPawn::GetEnemyState()
{
	if(!EnemyState)
		EnemyState = NewObject<UHOFEnemyState>();

	return EnemyState;
}

void AHOFEnemyPawn::OnSeePlayer(APawn * InPawn)
{
	SetCurrentState(EHOFEnemyState::ENEMY_CHASE);
	Instigator = InPawn;
}

void AHOFEnemyPawn::SetCurrentState(EHOFEnemyState newState)
{
	if (EnemyState->GetState() != EHOFEnemyState::ENEMY_DEAD)
	{
		Cast<AHOFEnemyController>(GetController())->SetStateInBlackBoard(newState);
		GetEnemyState()->SetState(newState);
	}
}