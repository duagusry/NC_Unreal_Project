// Fill out your copyright notice in the Description page of Project Settings.

#include "HOFBattleGameMode.h"
#include "Engine/World.h"
#include "HOFPlayerController.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

//�����ڴ� �𸮾󿡵��� ó�� �� �� �Ҹ��⶧���� ���⼭ ���� ���� �ϸ� ��κ��� �ٸ� ��ü���� ���� �ȵ� nullptr���� ���� �� Ȯ���� ����.
//�ʱ�ȭ�� ������ �����Ҷ� ȣ��Ǵ� BeginPlay����..
//�׷��� �����ڿ����� ����ü �������� �� �� ������..
AHOFBattleGameMode::AHOFBattleGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("Pawn'/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C'"));
	if (PlayerPawnObject.Class != NULL)
		DefaultPawnClass = PlayerPawnObject.Class;

	PlayerControllerClass = AHOFPlayerController::StaticClass();

	UE_LOG(LogClass, Warning, TEXT("BattleGameMode Start"));
}

void AHOFBattleGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UHOFGameInstance>(GetGameInstance());

	Counter = 3;
	GetWorldTimerManager().SetTimer(countDownHandle, this, &AHOFBattleGameMode::OnTimerTick, 1.0f, true);
	
	GameInstance->SetGamePlayState(EGameplayState::Battle);

	PlayerControllerClass = AHOFPlayerController::StaticClass();
}

void AHOFBattleGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHOFBattleGameMode::InitGameState()
{
	Super::InitGameState();
}

void AHOFBattleGameMode::OnTimerTick()
{
	//--Counter;
	UE_LOG(LogClass, Warning, TEXT("Count %d"), Counter);
	//Ÿ�̸� ����� WorldLevel ����
	/*
	if (Counter < 1)
	{
		g_PlayerData->EatFood();

		UE_LOG(LogClass, Warning, TEXT("Alive? %s"), g_PlayerData->IsAlive() ? TEXT("Alive") : TEXT("Dead"));
		
		GetWorld()->ServerTravel(FString("/Game/Maps/HOFWorldLevel"));
		GetWorldTimerManager().ClearTimer(countDownHandle);
	}
	*/
}


