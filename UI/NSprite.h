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
	FPoint mPos;
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

	void SetPos(FPoint& rCenter);
	bool IsDone() { return mDone; }
	Rect& Bounds();
};


#endif

