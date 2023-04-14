// Copyright Patrick Carvalho All Rights Reserved.
// sysware@sysware.com.br
// 

#include "FindWidget.h"

#include "Components/CheckBox.h"
#include "Components/ComboBox.h"
#include "Components/ComboBoxString.h"
#include "Kismet/GameplayStatics.h"


void UFindWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if (FindButton != nullptr)
    {
        FindButton->OnClicked.AddDynamic(this, &UFindWidget::OnFindClicked);
    }

    if (ClearButton != nullptr)
    {
        ClearButton->OnClicked.AddDynamic(this, &UFindWidget::OnClearClicked);
    }

    if (CheckHeuristic != nullptr)
    {
        CheckHeuristic->OnCheckStateChanged.AddDynamic(this, &UFindWidget::OnCheckClicked);
    }
    
    Grid = Cast<AMyPathBlockGrid>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyPathBlockGrid::StaticClass()));
    Setup();
}

void UFindWidget::Setup()
{
    nStart = Grid->Blocks[4];
    nEnd = Grid->Blocks[50]; 

    nStart->BlockMesh->SetMaterial(0, nStart->GreenMaterial);
    nEnd->BlockMesh->SetMaterial(0, nEnd->RedMaterial);

    // Reset navigation
    for (auto & node : Grid->Blocks)
    {
        node->bChecked = false;
        node->fGlobalCost = INFINITY;
        node->fLocalCost = INFINITY;
        node->parent = nullptr;
        node->bIsActive = false;
        node->bObstacle = false;
    }
}

bool UFindWidget::GetHeuristic()
{
    return  bHeuristic;
}

void UFindWidget::OnFindClicked()
{
    (new FAutoDeleteAsyncTask<MyPathTask>(Grid, nStart, nEnd, bHeuristic, ComboHeuristic->GetSelectedIndex()))->StartBackgroundTask();
}

void UFindWidget::LinkNodes(AMyPathBlock *n1, AMyPathBlock *n2)
{
    n1->AddLink(n2);
    n2->AddLink(n1);
}

void UFindWidget::OnClearClicked()
{
    for (int i = 0; i < (Grid->Size) * (Grid->Size); i++)
        Grid->Blocks[i]->BlockMesh->SetMaterial(0, Grid->Blocks[i]->BlueMaterial);

    Setup();
}

void UFindWidget::OnCheckClicked(bool bIsChecked)
{
    bHeuristic = bIsChecked;
}
