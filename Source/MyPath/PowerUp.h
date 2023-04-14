#pragma once

#ifndef POWER_UP_H
#define POWER_UP_H

#include "Vertex.h"

class PowerUp
{
public:
    enum PowerUpType
    {
        WEAPON,
        ARMOUR,
        HEALTH
    };
    
    PowerUp(const char* name, Vertex position)
    : mName(name), mPosition(position) 
    {
    }

    ~PowerUp()
    {
        delete mName;
    }
    
    PowerUpType GetPowerUpType() const
    {
        return mType;
    };

    const Vertex& GetPosition() const
    {
        return mPosition;
    }

protected:
    const char*  mName;
    Vertex       mPosition;
    PowerUpType  mType;
    
};

#endif // POWER_UP_H
