#pragma once
#ifndef LAYEROBJECT_H
#define LAYEROBJECT_H

#include "Shared.h"

struct SpriteInfo;

class LayerObjbect
{
private:
	SpriteInfo* info;
	float xVal; float yVal;
	bool m_delete;
public:
	LayerObjbect(int x, int y);
    void Draw(SDL_Surface *dest);
	bool RequestDelete() { return m_delete; };
};


#endif

