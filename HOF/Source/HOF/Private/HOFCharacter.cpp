// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFCharacter.h"
#include "HOF.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "HOFPlayerState.h"
#include "HOFGameInstance.h"
#include "HOFBattleGameMode.h"
#include "HOFItem.h"
#include "HOFGearItem.h"
#include "HOFWeaponItem.h"
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

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetSimulatePhysics(false);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, true);
	Weapon->AttachTo(GetMesh(), TEXT("weapon_r"));


	EquipStatus = CreateDefaultSubobject<AHOFEquipStatus>(TEXT("EquipStatus"));
}

// Called when the game starts or when spawned
void AHOFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerState = Cast<AHOFPlayerState>(GetController()->PlayerState);

	Cast<AHOFPlayerState>(PlayerState)->SetPlayerData(Cast<UHOFGameInstance>(GetGameInstance())->PlayerData);

	///////////////////////////////////////////////////////////////////////// For Test	///////////////////////////////////////////////////////////////////////////
	UWorld* World = GetWorld();

	//TSharedPtr<AHOFWeaponItem> DummyWeapon = MakeShared<AHOFWeaponItem>(World->SpawnActor<AHOFWeaponItem>(MyLoc, MyRot, SpawnInfo));
	AHOFWeaponItem* DummyWeapon = World->SpawnActor<AHOFWeaponItem>(GetActorLocation(), GetActorRotation(), FActorSpawnParameters());
	//Equip->Equip(ITEM_MAIN_WEAPON, DummyWeapon);
	EquipStatus->Equip(EHOFItemType::ITEM_MAIN_WEAPON, 0);
	///////////////////////////////////////////////////////////////////////// For Test	///////////////////////////////////////////////////////////////////////////
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

	AB_LOG(Warning, TEXT("HP:%f"), HOFPlayerState->PlayerData.HP.GetCurrentValue());

	if (!HOFPlayerState)
		return ActualDamage;

	if (HOFPlayerState->PlayerData.HP.CheckOnMinValue())
	{
		auto gameMode = Cast<AHOFBattleGameMode>(GetWorld()->GetAuthGameMode());
		gameMode->OnPlayerDead();
		return 0.f;
	}

	if (ActualDamage > 0.f)
	{
		HOFPlayerState->PlayerData.HP(-ActualDamage);
		//AB_LOG(Warning, TEXT("HP:%f"), HOFPlayerState->CurrentHP);

		if (HOFPlayerState->PlayerData.HP.CheckOnMinValue())
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
	float BaseDamage = 30.0f;

	// Get Attack Info from Current Weapon
	const auto& SlotItem = EquipStatus->GetEquippedItemBySlot(EHOFItemType::ITEM_MAIN_WEAPON);

	float WeaponDamage = 0.0f;
	
	do
	{
		if (!SlotItem)
			break;

		if (!SlotItem->IsWeaponItem())
			break;

		AHOFWeaponItem* Weapon = static_cast<AHOFWeaponItem*>(SlotItem);

		WeaponDamage += Weapon->GetAttackDamage();
	} while (0);

	float FinalDamage = BaseDamage + WeaponDamage;

	FPointDamageEvent PointDamageEvent(FinalDamage, HitResult, GetActorForwardVector(), UDamageType::StaticClass());
	HitResult.GetActor()->TakeDamage(FinalDamage, PointDamageEvent, GetController(), this);
}

void AHOFCharacter::Equip(EHOFItemType ItemType, int32 ItemId)
{
	UpdateEquipStatus(ItemType, ItemId);
	UpdateEquipedItem(ItemType);
}

void AHOFCharacter::UpdateEquipStatus(EHOFItemType ItemType, int32 ItemId)
{
	EquipStatus->Equip(ItemType, ItemId);
}

void AHOFCharacter::UpdateEquipedItem(EHOFItemType ItemType)
{
	auto Item = EquipStatus->GetEquippedItemBySlot(ItemType);

	if (Item)
	{
		if (ItemType == EHOFItemType::ITEM_MAIN_WEAPON)
			Weapon->SetSkeletalMesh(Item->GetMesh());
	}
}