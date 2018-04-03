#pragma once

#include "GameData.h"
#include "HOFWorldInput.generated.h"

//파라미터 두개를 넘기는 델리게이트 객체를 선언해줌.
DECLARE_DELEGATE_TwoParams(FOnePointActionDelegate, const FVector2D&, float);

#define COLLISION_WEAPON		ECC_GameTraceChannel1
#define COLLISION_PROJECTILE	ECC_GameTraceChannel2
#define COLLISION_PANCAMERA		ECC_GameTraceChannel3

#define BIND_1P_ACTION(Handler, ActionKey, ActionEvent, Delegate)	\
{ \
	int32 Idx = Handler->ActionBindings1P.AddZeroed(); \
	Handler->ActionBindings1P[Idx].Key = ActionKey; \
	Handler->ActionBindings1P[Idx].KeyEvent = ActionEvent; \
	Handler->ActionBindings1P[Idx].ActionDelegate.BindUObject(this, Delegate); \
}

struct FActionBinding
{
	EGameKey::Type Key;
	TEnumAsByte<EInputEvent> KeyEvent;
	FOnePointActionDelegate ActionDelegate;
};

struct FSimpleKeyState
{
	/** current events indexed with: IE_Pressed, IE_Released, IE_Repeat */
	uint8 Events[3];

	/** is it pressed? (unused in tap & hold) */
	uint8 bDown : 1;

	/** position associated with event */
	FVector2D Position;

	/** position associated with event */
	FVector2D Position2;

	/** accumulated down time */
	float DownTime;

	FSimpleKeyState()
	{
		FMemory::Memzero(this, sizeof(FSimpleKeyState));
	}
};

UCLASS()
class UHOFWorldInput : public UObject
{
	GENERATED_BODY()

	UHOFWorldInput() { }

public : 
	/** bindings for custom game events */
	TArray<FActionBinding> ActionBindings1P;

	/** update detection */
	//입력에 대한 매핑 처리
	void UpdateDetection(float DeltaTime);

protected : 
	/** update game key recognition */
	//키 매핑 처리
	void UpdateGameKeys(float DeltaTime);

	/** process input state and call handlers */
	void ProcessKeyStates(float DeltaTime);

	/** detect one point actions (touch and mouse) */
	void DetectOnePointActions(bool bCurrentState, bool bPrevState, float DeltaTime, const FVector2D& CurrentPosition, FVector2D& AnchorPosition, float& DownTime);



protected:
	/** game key states */
	TMap<EGameKey::Type, FSimpleKeyState> KeyStateMap;

	/** prev touch states for recognition */
	uint32 PrevTouchState;

	/** touch anchors */
	FVector2D TouchAnchors[2];

	/** how long was touch 0 pressed? */
	float Touch0DownTime;
};