// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFWorldPlayerController.h"
#include "HOFInputInterface.h"
#include "HOFWorldInput.h"

AHOFWorldPlayerController::AHOFWorldPlayerController()
{
	UE_LOG(LogClass, Warning, TEXT("WorldPlayerController Init"));
	PrimaryActorTick.bCanEverTick = true;
	bHidden = false;
	//WorldMode������ ���콺 Ŀ���� ����
	bShowMouseCursor = true;
}

void AHOFWorldPlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	if (!bGamePaused && PlayerInput && InputHandler)
	{
		//��ǲ�� ��ȭ�� ����
		InputHandler->UpdateDetection(DeltaTime);
	}

	Super::ProcessPlayerInput(DeltaTime, bGamePaused);


}

void AHOFWorldPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputHandler = NewObject<UHOFWorldInput>(this);

	BIND_1P_ACTION(InputHandler, EGameKey::Tap, IE_Pressed, &AHOFWorldPlayerController::OnTapPressed);
}

void AHOFWorldPlayerController::OnTapPressed(const FVector2D & ScreenPosition, float DownTime)
{
	UE_LOG(LogClass, Warning, TEXT("click"));
	FVector WorldPosition(0.f);
	AActor* const HitActor = GetClickedActor(ScreenPosition, WorldPosition);

	SetSelectedActor(HitActor, WorldPosition);

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UHOFInputInterface::StaticClass()))
	{
		IHOFInputInterface::Execute_OnInputTap(HitActor);
	}
}

AActor * AHOFWorldPlayerController::GetClickedActor(const FVector2D & ScreenPoint, FVector & WorldPoint)
{
	FHitResult Hit;
	if (GetHitResultAtScreenPosition(ScreenPoint, COLLISION_WEAPON, true, Hit))
	{
		WorldPoint = Hit.ImpactPoint;
		return Hit.GetActor();
	}

	return nullptr;
}

void AHOFWorldPlayerController::SetSelectedActor(AActor * NewSelectedActor, const FVector & NewPosition)
{
	if (SelectedActor != NewSelectedActor)
	{
		if (SelectedActor.IsValid())
		{
			SelectedActor = NewSelectedActor;
		}
	}
}
