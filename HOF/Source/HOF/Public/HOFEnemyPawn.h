// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HOFEnemyPawn.generated.h"

class UBlackboardData;
class UBehaviorTree;

UCLASS()
class HOF_API AHOFEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHOFEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision")
		class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Visible")
		class USkeletalMeshComponent* Body;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Visible")
		class UArrowComponent* Arrow;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Movement")
		class UFloatingPawnMovement*FloatPawnMovement;

	UPROPERTY(config, EditDefaultsOnly, BlueprintReadWrite, Category = "Stat")
		float MaxHP;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Stat")
		float CurrentHP;

	UPROPERTY(EditAnywhere, Category = Behavior)
		UBehaviorTree* behaviorTreeAsset;


private:
	float CurrentLeftRightVal;
	float CurrentUpDownVal;
};
