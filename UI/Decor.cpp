#include "Decor.h"
#include "Engine/SpriteResource.h"

Decor::Decor(std::string filename)
{
	info = &SpriteResource::RequestResource("UI", filename);
	xVal = rand() % _WSCREEN_WIDTH;
	yVal = rand() % _WSCREEN_WIDTH;
	
	clip = rand() % info->clip_count-1;
	if (clip == 0) show = true;
	else show = false;
	clipTimer.start();
}

void Decor::Update(int deltaTicks)
{
	Shared::CheckClip(clipTimer, clip, info->interval + rand() % 50, info->clip_count, 0);
	if (clip >= info->clip_count-1)
	{
		xVal = rand() % _WSCREEN_WIDTH;
		yVal = rand() % _WSCREEN_WIDTH;
		clip = rand() % 2;
		if (clip == 0) show = true;
		else show = false;
	}
	yVal += 50 * (deltaTicks/1000.f);
}

void Decor::Draw(SDL_Surface *dest)
{
	if (show)
		Shared::apply_surface(xVal, yVal, info->surface, dest, &info->clips[clip]);
}