// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFWorldPlayerController.h"
#include "HOFInputInterface.h"
#include "HOFWorldInput.h"
#include "HOFTextWidget.h"
#include "HOFPlayerState.h"
#include "HOFGameState.h"

AHOFWorldPlayerController::AHOFWorldPlayerController()
{
	UE_LOG(LogClass, Warning, TEXT("WorldPlayerController Init"));
	PrimaryActorTick.bCanEverTick = true;
	bHidden = false;
	//WorldMode에서는 마우스 커서가 보임
	bShowMouseCursor = true;

	//Initialize Widget
	BP_EventWidget = nullptr;
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> WorldEventWidgetBluePrint(TEXT("Blueprint'/Game/Blueprints/BP_EventWidget'"));

	if (WorldEventWidgetBluePrint.Object)
	{
		BP_EventWidget = CastChecked<UClass>(WorldEventWidgetBluePrint.Object->GeneratedClass);
	}
	
}

void AHOFWorldPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	GameState = GetWorld()->GetAuthGameMode()->GetGameState<AHOFGameState>();
}

void AHOFWorldPlayerController::ShowEventWidget(int32 id, AHOFWorldCardActor * pCard)
{
	EventWidget = CreateWidget<UHOFTextWidget>(this, BP_EventWidget); // Create Widget
	if (!EventWidget)
		return;

	EventWidget->Init(id, pCard);

	EventWidget->AddToViewport(); // Add it to the viewport so the Construct() method in the UUserWidget:: is run.
	EventWidget->SetVisibility(ESlateVisibility::Visible); // Set it to hidden so its not open on spawn.
	
}

void AHOFWorldPlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	if (CanProcessWorldInput() && !bGamePaused && PlayerInput && InputHandler)
	{
		//인풋의 변화를 감지
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

bool AHOFWorldPlayerController::CanProcessWorldInput()
{
	if (GameState->CurrentGameState != GAME_WORLD)
		return false;

	return true;
}
