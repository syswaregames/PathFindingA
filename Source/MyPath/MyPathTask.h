// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <list>

#include "CoreMinimal.h"
#include "MyPathBlockGrid.h"

class MYPATH_API MyPathTask : public FNonAbandonableTask
{
public:
	MyPathTask(AMyPathBlockGrid* _grid, AMyPathBlock * _nodeStart, AMyPathBlock *_nodeEnd,
				bool _heuristic, int _iheuristic);
	~MyPathTask();

	AMyPathBlockGrid* Grid;

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(PrimeSearchTask, STATGROUP_ThreadPoolAsyncTasks);
	}
	void DoWork();
	void LinkNodes(AMyPathBlock *n1, AMyPathBlock *n2);
	void AStarPath();
	float GetHeuristic(AMyPathBlock* a, AMyPathBlock* b);
	float GetManhattan(AMyPathBlock* a, AMyPathBlock* b);

	AMyPathBlock *nodeStart;
	AMyPathBlock *nodeEnd;
	bool bHeuristic;
	int iHeuristic;
};
