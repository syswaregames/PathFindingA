// Copyright Patrick Carvalho All Rights Reserved.
// sysware@sysware.com.br
// 

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputCoreTypes.h"
#include "MyPathBlock.generated.h"


/** A block that can be clicked */
UCLASS(minimalapi)
class AMyPathBlock : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;
    
    
public:
	AMyPathBlock();

	float         fLocalCost;
	float         fGlobalCost;
    
	bool		  bObstacle = false;
	bool          bChecked = false;
	AMyPathBlock  *parent;
	std::vector<AMyPathBlock*>  mLinks;

	void AddLink(AMyPathBlock *pathNode);
	const std::vector<AMyPathBlock*>& GetLinks() const;

	/** Are we currently active? */
	bool bIsActive;
    
    /** StaticMesh component for the clickable block */
    UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* BlockMesh;

	/** Pointer to white material used on the focused block */
	UPROPERTY()
	class UMaterial* BaseMaterial;

	/** Pointer to blue material used on inactive blocks */
	UPROPERTY()
	class UMaterialInstance* BlueMaterial;

	/** Pointer to orange material used on active blocks */
	UPROPERTY()
	class UMaterialInstance* OrangeMaterial;

	/** Pointer to orange material used on active blocks */
	UPROPERTY()
	class UMaterialInstance* BlackMaterial;

	UPROPERTY()
	class UMaterialInstance* RedMaterial;
	UPROPERTY()
	class UMaterialInstance* GreenMaterial;
	

	/** Grid that owns us */
	UPROPERTY()
	class AMyPathBlockGrid* OwningGrid;

	/** Handle the block being clicked */
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	/** Handle the block being touched  */
	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	void HandleClicked();

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }

};



