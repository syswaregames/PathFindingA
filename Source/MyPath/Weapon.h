#pragma once

#ifndef WEAPON_H
#define WEAPON_H

#include "PowerUp.h"

class Weapon : public PowerUp
{
public:
    Weapon(const char* name, Vertex position) :
        PowerUp(name, position)
    {
        mType = WEAPON;
        mDamageBonus = new int(0);
        mCriticalChanceBonus = new float(0);
    }
    
    ~Weapon()
    {
        delete mDamageBonus;
        delete mCriticalChanceBonus;
    }
    
    void SetCriticalChanceBonus(float* critical)
    {
        mCriticalChanceBonus = critical;
    }
    
    float* GetCriticalChanceBonus()
    {
        return mCriticalChanceBonus;
    }
    
    void SetDamageBonus(int* damage)
    {
        mDamageBonus = damage;
    }
    
    int* GetDamageBonus()
    {
        return mDamageBonus;
    }
protected:
    
    int* mDamageBonus;
    float* mCriticalChanceBonus;
};

#endif // WEAPON_H

