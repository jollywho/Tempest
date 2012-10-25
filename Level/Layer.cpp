#include "Layer.h"
#include "Game/Camera.h"

Layer::Layer(SDL_Surface* src, int height, int startPos)
{
	printf("Layer Created!\n");
	this->surface = src;
	this->height = height;
	this->start = startPos;
	this->xoffset = 0;
	yVal = 0; yVal2 = yVal - height;
	fixed = false; done = false;
	started = false;
}

Layer::Layer(SDL_Surface* src, int height, int startPos, int xoffset)
{
	printf("Layer Created!\n");
	this->surface = src;
	this->height = height;
	this->start = startPos;
	this->xoffset = xoffset;
	yVal = 0; yVal2 = yVal - height;
	fixed = true; done = false;
	started = false;
}

Layer::~Layer()
{
    printf("Layer Deleted\n");
	SDL_FreeSurface(surface);
}

void Layer::Start()
{
	if (!started)
	{
		started = true;
	}
}

void Layer::Update(Uint32 deltaTicks, float spd)
{
	if (done) return;
	
	if (started)
	{
		yVal += spd;
		yVal2 += spd;
		if (yVal > _G_BOUNDS_HEIGHT)
			yVal = yVal2-height;
		if (yVal2 > _G_BOUNDS_HEIGHT)
			yVal2 = yVal-height;
		bounds.y = 0;
		bounds.x = (int)Camera::CameraX();
	}
	if (Camera::CameraY() >= start && !fixed) Start();
}

void Layer::Draw(SDL_Surface *dest)
{
	if (done || !started) return;
	if (!fixed)
	{
	Shared::apply_surface(_G_BANNER_WIDTH, (int)yVal, surface, dest, &bounds);
	Shared::apply_surface(_G_BANNER_WIDTH, (int)yVal2, surface, dest, &bounds);
	}
	else
	{
	Shared::apply_surface(_G_BANNER_WIDTH + xoffset, (int)yVal, surface, dest, NULL);
	Shared::apply_surface(_G_BANNER_WIDTH + xoffset, (int)yVal2, surface, dest, NULL);
	}
}