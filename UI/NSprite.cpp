#include "NSprite.h"
#include "Engine/SpriteResource.h"

NSprite::NSprite(int x, int y, int size, int max_clips, int interval, SDL_Surface* src, bool stopclp, bool reverse)
{
	_useinfo = false;
	xVal = x; 
	yVal = y;
	clip_count = max_clips;
	clips = new SDL_Rect[clip_count];
	Shared::setFrames(clips ,max_clips, size, size);
	surface = src;
	stop = stopclp;
	clip = rand() % (max_clips-1);
	this->interval = interval;
	this->reverse = reverse;
	dir = -1;
	clip_Timer.start();
}

NSprite::NSprite(int x, int y, SpriteInfo* info, bool stopclp)
{
	_useinfo = true;
	xVal = x - info->width/2; 
	yVal = y - info->height/2;
	clip_count = info->clip_count;
	clips = info->clips;
	surface = info->surface;
	clip = 0; stop = stopclp;
	dir = -1;
	reverse = true;
	clip = rand() % (info->clip_count-1);
	this->interval = info->interval;
	clip_Timer.start();
}

NSprite::~NSprite() 
{
	if (!_useinfo)
		delete[] clips;
}

void NSprite::Reset()
{
	clip = 0;
}

void NSprite::Update()
{
	if (stop)
	{
		if (clip < clip_count)
			Shared::CheckClip(clip_Timer, clip, interval, clip_count, clip_count-1);
	}
	if (reverse)
	{
		if (clip_Timer.get_ticks() > interval)
		{ 
			if (clip > 0 && clip < clip_count-1)
				clip+=dir;
			else {
				dir = dir * -1; clip+=dir; }
			clip_Timer.start();
		}
	}
	else
		Shared::CheckClip(clip_Timer, clip, interval, clip_count, 0);
}

void NSprite::Draw(SDL_Surface *dest)
{
	Shared::apply_surface(xVal, yVal, surface, dest, &clips[clip]);
}