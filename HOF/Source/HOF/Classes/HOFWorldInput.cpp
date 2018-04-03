#include "HOFWorldInput.h"
#include "HOFWorldPlayerController.h"
#include "GameFramework/PlayerInput.h"

void UHOFWorldInput::UpdateDetection(float DeltaTime)
{
	UpdateGameKeys(DeltaTime);
	ProcessKeyStates(DeltaTime);
}

void UHOFWorldInput::UpdateGameKeys(float DeltaTime)
{
	//GetOuter �Լ��� �ڱ� �ڽ��� ������ �ִ� ��ü�� ��ȯ, �� ���� this(UHOFWorldInput)�� ������ �ִ� AHOFWorldPlayerController
	AHOFWorldPlayerController* MyController = Cast<AHOFWorldPlayerController>(GetOuter());

	uint32 CurrentTouchState = 0;
	for (int32 i = 0; i < ARRAY_COUNT(MyController->PlayerInput->Touches); i++)
	{
		//� �Է��� ���Դ��� �÷��׷� ǥ��
		if (MyController->PlayerInput->Touches[i].Z != 0)
		{
			CurrentTouchState |= (1 << i);
		}
	}

	//�̺�Ʈ �߻� ����Ʈ ���� �� ó��
	//������ �ܼ� Ŭ���� ������ �Ÿ� �� �κ��� ���� �ʿ� ���� ��..
	FVector2D LocalPosition = FVector2D(MyController->PlayerInput->Touches[0]);
	DetectOnePointActions(CurrentTouchState & 1, PrevTouchState & 1, DeltaTime, LocalPosition, TouchAnchors[0], Touch0DownTime);

	// save states
	PrevTouchState = CurrentTouchState;
}

void UHOFWorldInput::ProcessKeyStates(float DeltaTime)
{
	//���ε� �׼� �ڵ鷯 �Լ��� ȣ��.
	for (const FActionBinding& AB : ActionBindings1P)
	{
		const FSimpleKeyState* KeyState = KeyStateMap.Find(AB.Key);

		if (KeyState && KeyState->Events[AB.KeyEvent] > 0)
		{
			AB.ActionDelegate.ExecuteIfBound(KeyState->Position, KeyState->DownTime);
		}
	}

	// update states
	for (TMap<EGameKey::Type, FSimpleKeyState>::TIterator It(KeyStateMap); It; ++It)
	{
		FSimpleKeyState* const KeyState = &It.Value();

		if (KeyState->Events[IE_Pressed])
		{
			KeyState->bDown = true;
		}
		else if (KeyState->Events[IE_Released])
		{
			KeyState->bDown = false;
		}

		FMemory::Memzero(KeyState->Events, sizeof(KeyState->Events));
	}
}

void UHOFWorldInput::DetectOnePointActions(bool bCurrentState, bool bPrevState, float DeltaTime, const FVector2D & CurrentPosition, FVector2D & AnchorPosition, float & DownTime)
{
	//tap �̺�Ʈ�� hold �̺�Ʈ�� �����ϱ� ���� ����
	const float HoldTime = 0.3f;

	if (bCurrentState)
	{
		// just pressed? set anchor and zero time
		if (!bPrevState)
		{
			DownTime = 0;
			AnchorPosition = CurrentPosition;
		}
	}
	else
	{
		// just released? 
		if (bPrevState)
		{
			// tap detection
			if (DownTime < HoldTime)
			{
				FSimpleKeyState& TapState = KeyStateMap.FindOrAdd(EGameKey::Tap);
				TapState.Events[IE_Pressed]++;
				TapState.Position = AnchorPosition;
				TapState.DownTime = DownTime;
			}
		}
	}

}
