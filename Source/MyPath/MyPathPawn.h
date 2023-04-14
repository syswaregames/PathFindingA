// Copyright Patrick Carvalho All Rights Reserved.
// sysware@sysware.com.br
// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPathPawn.generated.h"

UCLASS(config=Game)
class AMyPathPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

protected:
	void OnResetVR();
	void TriggerClick();
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class AMyPathBlock* CurrentBlockFocus;
};
