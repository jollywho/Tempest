#pragma once
#ifndef DECOR_H
#define DECOR_H

#include "Engine/Shared.h"

struct SpriteInfo;

class Decor
{
private:
	SpriteInfo* info;
	float xVal; float yVal;
	int clip;
	Timer clipTimer;
	bool show;
public:
	Decor(std::string filename);
	void Update(int deltaTicks);
    void Draw(SDL_Surface *dest);
};


#endif

