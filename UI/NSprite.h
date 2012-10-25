#pragma once
#ifndef NSPRITE_H
#define NSPRITE_H

#include "Engine/Shared.h"

struct SpriteInfo;

class NSprite
{
private:
	bool _useinfo;
    int clip_count;
    int size;
    SDL_Rect* clips;
	int clip;
	int interval;
	SDL_Surface* surface;
	int xVal; int yVal;
	Timer clip_Timer;
	bool stop; bool reverse; int dir;
public:
	NSprite(int x, int y, int size, int max_clips, int interval, SDL_Surface* src, bool stop=false, bool reverse=false);
	NSprite(int x, int y, SpriteInfo* info, bool stop=false);
    ~NSprite();
    void Update();
    void Draw(SDL_Surface *dest);
	void Reset();
};


#endif

