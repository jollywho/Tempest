#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"
#include "Timer.h"

class Bullet
{
protected:
    int frame;
    Timer frame_Timer;
public:
    bool exploding;
    bool m_delete;
    bool RequestDelete() { return m_delete; }
    virtual void Update(Uint32 deltaTicks) {}
    virtual void Destroy() {}
    virtual void Draw(SDL_Surface *dest) {}
	Bullet() {}
    virtual ~Bullet() {}
};


#endif

