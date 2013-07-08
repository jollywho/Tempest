#pragma once
#ifndef ZOWN_H
#define ZOWN_H

#include "Enemy.h"

class Zown : public Enemy
{
	REGISTER(Zown);
private:
    Timer attack_Timer;
    double rot;
	int attackCount;
public:
    explicit Zown(int x, int y, std::list<Action*>& actions);
    ~Zown();
    void Attack();
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *pDest);
    static void Init();
    static void Cleanup();
    void TakeHit(int dmg);
};


#endif