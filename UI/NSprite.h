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
    int mSize;
    SDL_Rect* mpClips;
	int mClip;
	int mInterval;
	SDL_Surface* mpSurface;
	int mX; int mY;
	Timer mClipTimer;
	bool mStop; bool mReverse; int mDir;
public:
	NSprite(int x, int y, int size, int maxClips, int interval, SDL_Surface* pSrc, bool doesStop, bool isReverse=false);
	NSprite(int x, int y, SpriteInfo* pInfo, bool doesStop=false, bool isReverse=false);
    ~NSprite();
    void Update();
    void Draw(SDL_Surface *pDest);
	void Reset();
};


#endif

