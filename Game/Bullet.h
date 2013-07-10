#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Engine/Shared.h"

class Bullet
{
public:
    Bullet(int clip, bool del, bool explode) : mClip(clip), mDelete(del), mExplode(explode){};
    virtual void Update(const int& rDeltaTime) = 0;
    virtual void Draw(SDL_Surface *pDest) = 0;
    bool RequestDelete() { return mDelete; }
protected:
	bool mExplode;
	bool mDelete;
    int mClip;
    Timer mClipTimer;
};


#endif