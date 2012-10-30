#pragma once
#ifndef LAYEROBJECT_H
#define LAYEROBJECT_H

#include "Shared.h"

struct SpriteInfo;

class LayerObjbect
{
private:
	SpriteInfo* mpInfo;
	float xVal; float yVal;
	bool mDelete;
public:
	LayerObjbect(int x, int y);
    void Draw(SDL_Surface *pDest);
	bool RequestDelete() { return mDelete; };
};


#endif

