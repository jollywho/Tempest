#include "NSprite.h"
#include "Engine/SpriteResource.h"

NSprite::NSprite(int x, int y, int size, int maxClips, int interval, SDL_Surface* pSrc, bool doesStop, bool isReverse)
{
	mUseInfo = false;
	mX = x; 
	mY = y;
	mMaxClip = maxClips;
	mpClips = new SDL_Rect[maxClips];
	Shared::SetFrames(mpClips, maxClips, size, size);
	mpSurface = pSrc;
	mStop = doesStop;
	mClip = rand() % (maxClips-1);
	mInterval = interval;
	mReverse = isReverse;
	mDir = -1;
	mClipTimer.Start();
}

NSprite::NSprite(int x, int y, SpriteInfo* pInfo, bool doesStop, bool isReverse)
{
	mUseInfo = true;
	mX = x - pInfo->width/2; 
	mY = y - pInfo->height/2;
	mMaxClip = pInfo->maxClips;
	mpClips = pInfo->pClips;
	mpSurface = pInfo->pSurface;
	mClip = 0; mStop = doesStop;
	mDir = -1;
	mReverse = isReverse;
	mClip = rand() % (pInfo->maxClips-1);
	mInterval = pInfo->interval;
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
	if (mStop)
	{
		if (mClip < mMaxClip)
			Shared::CheckClip(mClipTimer, mClip, mInterval, mMaxClip, mMaxClip-1);
	}
	if (mReverse)
	{
		if (mClipTimer.GetTicks() > mInterval)
		{ 
			if (mClip > 0 && mClip < mMaxClip-1)
				mClip+=mDir;
			else {
				mDir = mDir * -1; mClip+=mDir; }
			mClipTimer.Start();
		}
	}
	else
		Shared::CheckClip(mClipTimer, mClip, mInterval, mMaxClip, 0);
}

void NSprite::Draw(SDL_Surface *pDest)
{
	Shared::DrawSurface(mX, mY, mpSurface, pDest, &mpClips[mClip]);
}