#pragma once
#ifndef NSPRITE_H
#define NSPRITE_H

#include "Engine/Shared.h"

struct SpriteInfo;

class NSprite
{
private:
	bool mUseInfo;
    int mMaxClip;
    int size;
    SDL_Rect* mpClips;
	int mClip;
	int interval;
	SDL_Surface* mpSurface;
	int mX; int mY;
	Timer mClipTimer;
	bool stop; bool reverse; int dir;
public:
	NSprite(int x, int y, int size, int maxClips, int interval, SDL_Surface* pSrc, bool stopclp, bool reverse=false);
	NSprite(int x, int y, SpriteInfo* pInfo, bool stop=false);
    ~NSprite();
    void Update();
    void Draw(SDL_Surface *pDest);
	void Reset();
};


#endif

