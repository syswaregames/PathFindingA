#pragma once

#ifndef PATH_NODE_H
#define PATH_NODE_H

#include "Vertex.h"
#include "PowerUp.h"

#include <vector>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

class PathNode;
typedef vector<PathNode*> PathNodes;

class PathNode
{
public:
    PathNode(const char* name, Vertex position) :
        mName(name), mPosition(position)
    {
    }
    
    ~PathNode()
    {
        //delete mName;
        mLinks.clear();
        mPowerUps.clear();
    }

    void AddLink(PathNode *pathNode)
    {
        mLinks.push_back(pathNode);
    }
    
    void RemoveLink(PathNode *pathNode)
    {
        PathNodes::iterator i = find(mLinks.begin(), mLinks.end(), pathNode);
        mLinks.erase(i); 
    }

    void AddPowerUp(PowerUp *powerUp)
    {
        mPowerUps.push_back(powerUp);
    }
    
    void RemovePowerUp(PowerUp *powerUp)
    {
        vector<PowerUp*>::iterator i = find(mPowerUps.begin(), mPowerUps.end(), powerUp);
        mPowerUps.erase(i);
    }

    const FString GetName() const
    {
        return mName;
    }

    const PathNodes& GetLinks() const
    {
        return mLinks;
    }

    const vector<PowerUp*> GetPowerUps() const
    {
        return mPowerUps;
    }
    
    const Vertex& GetPosition()
    {
        return mPosition;
    }
    
    
    float         fLocalCost;
    float         fGlobalCost;
    
    bool          bObstacle = false;
    bool          bChecked = false;
    PathNode*     parent;
    

protected:
    const FString    mName;
    Vertex           mPosition;
    

    PathNodes        mLinks;    
    vector<PowerUp*> mPowerUps;
    
};

#endif // PATH_NODE_H
