// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HOFPlayerState.h"
#include "Runtime/Engine/Classes/Animation/AnimSequence.h"
#include "HOFEnemyPawn.generated.h"

UENUM(BlueprintType)
enum EHOFEnemyAnimation
{
	ANIM_IDLE UMETA(DisplayName = "ANIM_IDLE"),
	ANIM_RUN UMETA(DisplayName = "ANIM_RUN"),
	ANIM_DEAD UMETA(DisplayName = "ANIM_DEAD"),
	ANIM_ATTACK UMETA(DisplayName = "ANIM_ATTACK"),
};

class UPawnSensingComponent;
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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//virtual AActor SpawnActor();
	float TakeDamage(float Damage, const FDamageEvent & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		TMap<TEnumAsByte<EHOFEnemyAnimation>, UAnimSequence*> AnimationMap;

	UFUNCTION(BlueprintCallable)
		bool IsRunning();

	UFUNCTION(BlueprintCallable)
		bool IsDead();

	UFUNCTION(BlueprintCallable)
		AHOFPlayerState* GetEnemyState();

	UFUNCTION(BlueprintCallable)
		void SetCurrentState(EHOFCharacterState newState);

	UFUNCTION(BlueprintCallable, Category = "Damage")
		void AttackHit();

private:
	AHOFPlayerState *enemyState;
	UPawnSensingComponent *PawnSenses;
	float CurrentLeftRightVal;
	float CurrentUpDownVal;
	bool isDead;
	
	TSharedPtr<FCollisionObjectQueryParams> GetTraceObject(const TArray<ECollisionChannel>& channels);
	TSharedPtr<FCollisionQueryParams> GetTraceParams();
	void GiveDamage(const FHitResult & HitResult);

	UFUNCTION()
		void OnSeePlayer(APawn *InPawn);
};
