// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFCharacter.h"
#include "HOF.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "HOFPlayerState.h"
#include "DrawDebugHelpers.h"

// Sets default values
AHOFCharacter::AHOFCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachTo((USceneComponent*)GetCapsuleComponent());
	SpringArm->TargetArmLength = 650.0f;
	SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(SpringArm);

	//Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
}

// Called when the game starts or when spawned
void AHOFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHOFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHOFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHOFCharacter::PossessedBy(AController * NewController)
{
	UClass *AnimInstanceClass = AnimAssetClass.TryLoadClass<UAnimInstance>();
	if (AnimInstanceClass)
	{
		UE_LOG(LogClass, Warning, TEXT("Loading Character Anim Asset.. "));
		GetMesh()->SetAnimInstanceClass(AnimInstanceClass);
	}
}

float AHOFCharacter::TakeDamage(float Damage, const FDamageEvent &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	AHOFPlayerState* HOFPlayerState = Cast<AHOFPlayerState>(PlayerState);

	if (!HOFPlayerState)
		return ActualDamage;

	if (HOFPlayerState->CurrentHP <= 0.f)
		return 0.f;

	if (ActualDamage > 0.f)
	{
		HOFPlayerState->CurrentHP = FMath::Clamp(HOFPlayerState->CurrentHP - ActualDamage, 0.0f, HOFPlayerState->MaxHP);
		AB_LOG(Warning, TEXT("HP:%f"), HOFPlayerState->CurrentHP);

		if (HOFPlayerState->CurrentHP <= 0)
			HOFPlayerState->SetState(EHOFCharacterState::PLAYER_DEAD);
	}
	return ActualDamage;
}

void AHOFCharacter::AttackHit()
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

TSharedPtr<FCollisionQueryParams> AHOFCharacter::GetTraceParams()
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

TSharedPtr<FCollisionObjectQueryParams> AHOFCharacter::GetTraceObject(const TArray<ECollisionChannel> &channels)
{
	auto TraceObject = MakeShared<FCollisionObjectQueryParams>();
	for(auto channel : channels)
		TraceObject->AddObjectTypesToQuery(channel);
	return TraceObject;
}

void AHOFCharacter::GiveDamage(const FHitResult &HitResult)
{
	AB_LOG(Warning, TEXT("HitActor=%s"), *(HitResult.GetActor()->GetName()));
	float BaseDamage = 100.0f;

	FPointDamageEvent PointDamageEvent(BaseDamage, HitResult, GetActorForwardVector(), UDamageType::StaticClass());
	HitResult.GetActor()->TakeDamage(BaseDamage, PointDamageEvent, GetController(), this);
}