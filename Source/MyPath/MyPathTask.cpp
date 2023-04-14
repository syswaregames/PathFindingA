// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPathTask.h"

#include "FindWidget.h"


// For this example, all links are symmetric.
/*
inline void LinkNodes(PathNode *n1, PathNode *n2)
{
    n1->AddLink(n2);
    n2->AddLink(n1);
}
*/
    
MyPathTask::MyPathTask(AMyPathBlockGrid* _grid, AMyPathBlock * _nodeStart, AMyPathBlock *_nodeEnd,
                        bool _heuristic, int _iheuristic)
{
    Grid = _grid;
    nodeStart = _nodeStart;
    nodeEnd = _nodeEnd;
    bHeuristic = _heuristic;
    iHeuristic = _iheuristic;
}

MyPathTask::~MyPathTask()
{
    UE_LOG(LogTemp, Warning, TEXT("Task Finished!"));
}

void MyPathTask::DoWork()
{
    UE_LOG(LogTemp, Warning, TEXT("Started!"));

    // Create connections - in this case nodes are on a regular grid
    int nMapWidth = Grid->Size;
    int nMapHeight = Grid->Size;
    
    for (int x = 0; x < nMapWidth; x++)
        for (int y = 0; y < nMapHeight; y++)
        {
            if( y > 0 )
                LinkNodes(Grid->Blocks[y*nMapWidth + x], Grid->Blocks[(y - 1) * nMapWidth + (x + 0)]);
            if( y < nMapHeight - 1)
                LinkNodes(Grid->Blocks[y*nMapWidth + x], Grid->Blocks[(y + 1) * nMapWidth + (x + 0)]);
            if ( x > 0)
                LinkNodes(Grid->Blocks[y*nMapWidth + x], Grid->Blocks[(y + 0) * nMapWidth + (x - 1)]);
            if(x<nMapWidth - 1)
                LinkNodes(Grid->Blocks[y*nMapWidth + x], Grid->Blocks[(y + 0) * nMapWidth + (x + 1)]);
        }
    AStarPath();
}

void MyPathTask::LinkNodes(AMyPathBlock *n1, AMyPathBlock *n2)
{
    n1->AddLink(n2);
    n2->AddLink(n1);
}

// Manhattan Method
float MyPathTask::GetManhattan(AMyPathBlock* a, AMyPathBlock* b)
{
    return abs((a->GetTransform().GetLocation().X - b->GetTransform().GetLocation().X) +
                       (a->GetTransform().GetLocation().Y - b->GetTransform().GetLocation().Y));
}


// Diagonal Shortcut
float MyPathTask::GetHeuristic(AMyPathBlock* a, AMyPathBlock* b)
{
    
    return sqrtf( (a->GetTransform().GetLocation().X - b->GetTransform().GetLocation().X) * (a->GetTransform().GetLocation().X - b->GetTransform().GetLocation().X) +
                  (a->GetTransform().GetLocation().Y - b->GetTransform().GetLocation().Y) * (a->GetTransform().GetLocation().Y - b->GetTransform().GetLocation().Y) );
}

/*
 A* path finding algorithm is a widely and really powerful
 shortest path finding node algorithm.
 A heuristic is used to bias the algorithm towards success.

 // ***************************************************************************
 // * Pseudo-code                                                             *
 // ***************************************************************************
 //
 // Reset the navigation
 // Current node is the start and add to not tested list
 // Loop while if the not tested list contains nodes and is not the end node
 //     Sort Untested nodes by global goal, so lowest is first
 //     Pop front all visted nodes and test if listNotTestedNodes not empty
 //     get the first listNotTestedNodes -> Front
 //     if listNotTestedNodes is empty then abort
 //     set current node as the first listNotTestedNodes
 //     set current node as visited
 //     loop current node links (neighbours)
 //         if neighbour is not visited push back to not tested nodes
 //         calculate the neighbours potential lowest parent distance
 //         If this node is a lower distance, use this node
 //             update the neighbour's heuristic
 //
*/

void MyPathTask::AStarPath() 
{
    // Reset navigation
    for (auto &node : Grid->Blocks)
    {
        node->bChecked = false;
        node->fGlobalCost = INFINITY;
        node->fLocalCost = INFINITY;
        node->parent = nullptr;
    }
    
    // inicialization
    AMyPathBlock *nodeCurrent = nodeStart;
    nodeStart->fLocalCost = 0.0f;

    if (bHeuristic)
        nodeStart->fGlobalCost = GetHeuristic(nodeStart, nodeEnd);
    else
        nodeStart->fGlobalCost = 1; //GetHeuristic(nodeStart, nodeEnd);
    
    std::list<AMyPathBlock*> listNotCheckedNodes;
    
    // add the start node to not checked nodes
    // this will ensure it gets tested
    listNotCheckedNodes.push_back(nodeStart);
    
    // if the not checked nodes is not empty
    // we need to check paths which may not yet been explored
    // and make sure it wont be the longest
    while (!listNotCheckedNodes.empty() && nodeCurrent != nodeEnd)
    {
        // sort untested nodes by GlobalCost, so lowest is first
        listNotCheckedNodes.sort([](const AMyPathBlock* a, const AMyPathBlock* b){ return a->fGlobalCost < b->fGlobalCost; } );
        
        // front is the lowest distance node or remove if have been visited
        while(!listNotCheckedNodes.empty() && listNotCheckedNodes.front()->bChecked)
            listNotCheckedNodes.pop_front();
           
        // get the current selected node and print on screen
        AMyPathBlock *node = listNotCheckedNodes.front();
        
        // all nodes checked? stop!
        if (listNotCheckedNodes.empty())
        {
        	break;
        }

        nodeCurrent = listNotCheckedNodes.front();
        
        // check the node only once
        nodeCurrent->bChecked = true;
        
        
        if (nodeCurrent)
        {
            nodeCurrent->BlockMesh->SetMaterial(0, node->OrangeMaterial);
            FPlatformProcess::Sleep(0.15f);
        }
        
        // loop each of this node's links (Neighbours)
        for (auto nodeLinks : nodeCurrent->GetLinks())
        {
            // Add to not checked nodes list only if is not checked
            // and it's not a obstacle, the obstacle isn't necessary in
            // this situation, but very usefull in production/gameplay
            if (!nodeLinks->bChecked && nodeLinks->bObstacle == false)
                listNotCheckedNodes.push_back(nodeLinks);
            
            float fLowerCost = 0;
            
            if (bHeuristic)
            {
                if (iHeuristic == 0)
                    fLowerCost = nodeCurrent->fLocalCost + GetHeuristic(nodeCurrent, nodeLinks);
                else
                    fLowerCost = nodeCurrent->fLocalCost + GetManhattan(nodeCurrent, nodeLinks); 
            }
            else
                fLowerCost = nodeCurrent->fLocalCost + 1;
            
            if (fLowerCost < nodeLinks->fLocalCost)
            {
                // The heuristic is used to the path algorithm, so it knows if its getting
                // better or worse.
                // update  NodeLink's global cost
                nodeLinks->parent = nodeCurrent;
                nodeLinks->fLocalCost = fLowerCost;

                if (bHeuristic)
                {
                    if (iHeuristic == 0)
                        nodeLinks->fGlobalCost = nodeLinks->fLocalCost + GetHeuristic(nodeLinks, nodeEnd);
                    else
                        nodeLinks->fGlobalCost = nodeLinks->fLocalCost + GetManhattan(nodeLinks, nodeEnd); 
                }
                else
                    nodeLinks->fGlobalCost = nodeLinks->fLocalCost + 1;
            }
            
        }
        
    }
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Done! ")));
}
