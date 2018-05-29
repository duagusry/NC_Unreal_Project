// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFCharacter.h"
#include "HOF.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"

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

