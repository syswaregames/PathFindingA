// Copyright Patrick Carvalho All Rights Reserved.
// sysware@sysware.com.br
// 

#include "MyPathBlockGrid.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "AMyPathBlockGrid"

AMyPathBlockGrid::AMyPathBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", ""), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 6;
    BlockSpacing = 150.f; //300.f;
}


void AMyPathBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex/Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		AMyPathBlock* NewBlock = GetWorld()->SpawnActor<AMyPathBlock>(BlockLocation, FRotator(0,0,0));
        
		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
		}
        
        Blocks.Add(NewBlock);

		// sPathNodes
		
		//const char* cname = StringCast<ANSICHAR>(*NewBlock->GetName()).Get();
        //sPathNodes.push_back(new PathNode(cname, Vertex(BlockLocation.X, BlockLocation.Y, 0), NewBlock));
	}

	
    /*
    if (Blocks[10])
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Block[10] Set !"));
	
	
	if (Blocks[10]->OrangeMaterial)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Orange set"));
		Blocks[10]->BlockMesh->SetMaterial(0, Blocks[10]->BlackMaterial);

	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Orange NOT set"));
     */
	


}


void AMyPathBlockGrid::AddScore()
{
	// Increment score
	//Score++;

	// Update text
    ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "ZXcZXC"), FText::AsNumber(0)));
    
}

#undef LOCTEXT_NAMESPACE
