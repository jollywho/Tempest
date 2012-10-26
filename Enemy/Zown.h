#pragma once
#ifndef ZOWN_H
#define ZOWN_H

#include "Enemy.h"

class Zown : public Enemy
{
private:
    Timer attack_Timer;
    double rot;
	int attackCount;
public:
    Zown(int x, int y);
    ~Zown();
    void Attack();
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *dest);
    static void Init();
    static void CleanUp();
    void TakeHit(int dmg);
};


#endif