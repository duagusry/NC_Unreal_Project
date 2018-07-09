// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameData.h"
#include "HOFWorldPlayerController.h"
#include "HOFWorldPawn.generated.h"

UCLASS()
class HOF_API AHOFWorldPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHOFWorldPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	BaseStructs::Position GetPosition();

	// WorldBoardActor에서의 위치 설정
	void SetPosition(int x, int y);

	// Pawn의 Location 정보 변경
	void SetLocation(FVector location);

	// 목표 CardActor의 위치 정보를 받아서 Pawn의 Rotation 정보 변경
	void SetRotation(FVector targetCardLocation);

	BaseStructs::Position m_Position;
	AHOFWorldPlayerController* PlayerController;
	
};
