#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Engine/Shared.h"

class Bullet
{
public:
    virtual ~Bullet() {}    
    bool RequestDelete() { return m_delete; }
    virtual void Update(const int& iElapsedTime) = 0;
    virtual void Draw(SDL_Surface *dest) = 0;
protected:
	bool exploding;
	bool m_delete;
    int clip;
    Timer clip_timer;
};


#endif

