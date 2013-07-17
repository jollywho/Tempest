#pragma once
#ifndef NSPRITE_H
#define NSPRITE_H

#include "Engine/Shared.h"

struct SpriteInfo;

class NSprite
{
private:
	SpriteInfo* mpInfo;

	int mClip;
	HitBox mBounds;
	Timer mClipTimer;

	int mDir;
	bool mStop; 
	bool mReverse; 
	bool mDone;
public:
	explicit NSprite(float x, float y, SpriteInfo* pInfo, bool doesStop=false, bool isReverse=false);
    ~NSprite();

    void Update();
    void Draw(SDL_Surface *pDest);
	void Reset();

	void SetPos(Point& rCenter);
	bool IsDone() { return mDone; }
	HitBox& GetBounds() { return mBounds; }
};


#endif

