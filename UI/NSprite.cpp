#include "NSprite.h"
#include "Engine/SpriteResource.h"

NSprite::NSprite(int x, int y, int size, int maxClips, int interval, SDL_Surface* pSrc, bool stopclp, bool reverse)
{
	mUseInfo = false;
	mX = x; 
	mY = y;
	mMaxClip = maxClips;
	mpClips = new SDL_Rect[maxClips];
	Shared::SetFrames(mpClips, maxClips, size, size);
	mpSurface = pSrc;
	stop = stopclp;
	mClip = rand() % (maxClips-1);
	this->interval = interval;
	this->reverse = reverse;
	dir = -1;
	mClipTimer.Start();
}

NSprite::NSprite(int x, int y, SpriteInfo* pInfo, bool stopclp)
{
	mUseInfo = true;
	mX = x - pInfo->width/2; 
	mY = y - pInfo->height/2;
	mMaxClip = pInfo->maxClips;
	mpClips = pInfo->pClips;
	mpSurface = pInfo->pSurface;
	mClip = 0; stop = stopclp;
	dir = -1;
	reverse = true;
	mClip = rand() % (pInfo->maxClips-1);
	this->interval = pInfo->interval;
	mClipTimer.Start();
}

NSprite::~NSprite() 
{
	if (!mUseInfo)
		delete[] mpClips;
}

void NSprite::Reset()
{
	mClip = 0;
}

void NSprite::Update()
{
	if (stop)
	{
		if (mClip < mMaxClip)
			Shared::CheckClip(mClipTimer, mClip, interval, mMaxClip, mMaxClip-1);
	}
	if (reverse)
	{
		if (mClipTimer.GetTicks() > interval)
		{ 
			if (mClip > 0 && mClip < mMaxClip-1)
				mClip+=dir;
			else {
				dir = dir * -1; mClip+=dir; }
			mClipTimer.Start();
		}
	}
	else
		Shared::CheckClip(mClipTimer, mClip, interval, mMaxClip, 0);
}

void NSprite::Draw(SDL_Surface *pDest)
{
	Shared::DrawSurface(mX, mY, mpSurface, pDest, &mpClips[mClip]);
}