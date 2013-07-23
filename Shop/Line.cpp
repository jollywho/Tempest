#include "Line.h"
#include "Engine/SpriteResource.h"

Line::Line(Point p, int dir)
{
	if (dir == 0)
		mpSurface = &SpriteResource::RequestTextureResource("Shop",
			"line_vertical");
	else
		mpSurface = &SpriteResource::RequestTextureResource("Shop",
			"line_horizontal");
	mPos = p;
}


void Line::Update(Uint32 deltaTicks)
{

}

void Line::Draw(SDL_Surface *pDest)
{
	Shared::DrawSurface(mPos.x, mPos.y, mpSurface->pSurface, pDest);
}