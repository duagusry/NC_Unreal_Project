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
	//GetOuter 함수는 자기 자신을 가지고 있는 객체를 반환, 이 경우는 this(UHOFWorldInput)를 가지고 있는 AHOFWorldPlayerController
	AHOFWorldPlayerController* MyController = Cast<AHOFWorldPlayerController>(GetOuter());

	uint32 CurrentTouchState = 0;
	for (int32 i = 0; i < ARRAY_COUNT(MyController->PlayerInput->Touches); i++)
	{
		//어떤 입력이 들어왔는지 플래그로 표시
		if (MyController->PlayerInput->Touches[i].Z != 0)
		{
			CurrentTouchState |= (1 << i);
		}
	}

	//이벤트 발생 포인트 감지 후 처리
	//솔직히 단순 클릭만 구현할 거면 이 부분이 굳이 필요 없을 듯..
	FVector2D LocalPosition = FVector2D(MyController->PlayerInput->Touches[0]);
	DetectOnePointActions(CurrentTouchState & 1, PrevTouchState & 1, DeltaTime, LocalPosition, TouchAnchors[0], Touch0DownTime);

	// save states
	PrevTouchState = CurrentTouchState;
}

void UHOFWorldInput::ProcessKeyStates(float DeltaTime)
{
	//매핑된 액션 핸들러 함수를 호출.
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
	//tap 이벤트와 hold 이벤트를 구분하기 위한 기준
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
