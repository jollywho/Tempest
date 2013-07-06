#pragma once
#ifndef DECOR_H
#define DECOR_H

#include "Engine/Shared.h"

struct SpriteInfo;

class Decor
{
private:
	SpriteInfo* mpInfo;
	float mX; float mY;
	int mClip;
	Timer mClipTimer;
	bool show;
public:
	Decor();
	void Update(int deltaTicks);
    void Draw(SDL_Surface *pDest);
};


#endif

