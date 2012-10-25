#include "LayerObject.h"
#include "Quartz.h"
#include "SpriteResource.h"
#include "playstate.h"
#include "Camera.h"

LayerObjbect::LayerObjbect(int x, int y)
{
	m_delete = false;
	info = &SpriteResource::RequestResource("Explosions", "Residue.png");
	xVal = x-info->width/2;
	yVal = y-info->height/2;
	CPlayState::Instance()->itemList.push_back(new Quartz(xVal + info->width/2, yVal+Camera::CameraY2 + info->height/2, 50));
}

void LayerObjbect::Draw(SDL_Surface *dest)
{
	Camera::DrawSurface(xVal, yVal, info->surface, dest, NULL);
}