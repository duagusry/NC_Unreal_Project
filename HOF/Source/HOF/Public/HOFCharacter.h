// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HOFCharacter.generated.h"

UCLASS(config=Game)
class HOF_API AHOFCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHOFCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(class AController *NewController) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision")
		class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Visible")
		class USkeletalMeshComponent* Body;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Visible")
		class UArrowComponent* Arrow;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		class UFloatingPawnMovement*FloatPawnMovement;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* Camera;

	UPROPERTY(config, EditDefaultsOnly, BlueprintReadWrite, Category = "Stat")
		float MaxHP;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Stat")
		float CurrentHP;

	UPROPERTY(config)
		TArray<FStringAssetReference>CharacterAssets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
		bool isAttacking;

	UPROPERTY(config)
		FStringClassReference AnimAssetClass;
};
