#pragma once
#ifndef LINE_H
#define LINE_H

#include "Engine/Shared.h"

struct TextureInfo;

class Line
{
private:
	int mDir;
	Point mPos;
	TextureInfo* mpSurface;
public:
	Line(Point p, int dir);
	~Line(){};
	void Update(Uint32 deltaTicks);
	void Draw(SDL_Surface *pDest);
	Point& GetPos() { return mPos; }
};

#endif

