// Copyright Patrick Carvalho All Rights Reserved.
// sysware@sysware.com.br
// 

#pragma once


#include "CoreMinimal.h"
#include "MyPathBlock.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"
#include "UObject/ConstructorHelpers.h"
#include "MyPathBlockGrid.generated.h"


class AMyPathBlock;

UCLASS(minimalapi)
class AMyPathBlockGrid final : public AActor
{
	
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;

public:
	AMyPathBlockGrid();

	/** How many blocks have been clicked */
	int32 Score;

	/** Number of blocks along each side of grid */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size;

	/** Spacing of blocks */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;
    
    // UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)

	TArray<AMyPathBlock*> Blocks;

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

public:

	/** Handle the block being clicked */
	void AddScore();

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }
};



