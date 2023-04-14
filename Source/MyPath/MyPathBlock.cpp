// Copyright Patrick Carvalho All Rights Reserved.
// sysware@sysware.com.br
// 

#include "MyPathBlock.h"

AMyPathBlock::AMyPathBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlackMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> RedMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> GreenMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
			, BlackMaterial(TEXT("/Game/Puzzle/Meshes/BlackMaterial.BlackMaterial"))
			, RedMaterial(TEXT("/Game/Puzzle/Meshes/RedMaterial.RedMaterial"))
			, GreenMaterial(TEXT("/Game/Puzzle/Meshes/GreenMaterial.GreenMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(0.5f,0.5f,0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
    //BlockMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());
    BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	
	BlockMesh->OnClicked.AddDynamic(this, &AMyPathBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &AMyPathBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
	BlackMaterial = ConstructorStatics.BlackMaterial.Get();
	RedMaterial = ConstructorStatics.RedMaterial.Get();
	GreenMaterial = ConstructorStatics.GreenMaterial.Get();

}

void AMyPathBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void AMyPathBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void AMyPathBlock::HandleClicked()
{
	// Check we are not already active
	if (!bIsActive)
	{
		bIsActive = true;
		
		// Change material
		BlockMesh->SetMaterial(0, BlackMaterial);
		bObstacle = true;
	}

}

void AMyPathBlock::AddLink(AMyPathBlock *pathNode)
{
	mLinks.push_back(pathNode);
}

const std::vector<AMyPathBlock*>& AMyPathBlock::GetLinks() const
{
	return mLinks;
}


