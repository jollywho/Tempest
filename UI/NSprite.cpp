#include "NSprite.h"
#include "Engine/SpriteResource.h"

NSprite::NSprite(float x, float y, SpriteInfo* pInfo, bool doesStop, bool isReverse)
	: mBounds(x, y, pInfo->width, pInfo->height)
{
	mBounds.rect.x = x - pInfo->width/2; 
	mBounds.rect.y = y - pInfo->height/2;

	mpInfo = pInfo;
	mDir = -1;
	mClip = 0; 

	mStop = doesStop;
	mReverse = isReverse;
	mDone = false;
	mClip = rand() % (pInfo->maxClips-1);

	mClipTimer.Start();
}

NSprite::~NSprite() 
{
}

void NSprite::Reset()
{
	mClip = 0;
	mDone = false;
	mClipTimer.Start();
}

void NSprite::SetPos(Point& rCenter)
{
	mBounds.rect.x = rCenter.x - mpInfo->width/2; 
	mBounds.rect.y = rCenter.y - mpInfo->height/2;
}

void NSprite::Update()
{
	if (mDone) return;
	if (mReverse)
	{
		if (mClipTimer.GetTicks() > mpInfo->interval)
		{ 
			if (mClip > 0 && mClip < mpInfo->maxClips-1)
				mClip+=mDir;
			else {
				mDir = mDir * -1; mClip+=mDir; }
			mClipTimer.Start();
		}
	}
	else if (mStop && !mDone)
	{
		Shared::CheckClip(mClipTimer, mClip, mpInfo->interval, mpInfo->maxClips, mpInfo->maxClips);
		mDone = mClip >= mpInfo->maxClips? true: false;
	}
	else
		Shared::CheckClip(mClipTimer, mClip, mpInfo->interval, mpInfo->maxClips, 0);
}

void NSprite::Draw(SDL_Surface *pDest)
{
	if (mDone) return;
	Shared::DrawSurface(mBounds.rect.x, mBounds.rect.y, mpInfo->pSurface, pDest, &mpInfo->pClips[mClip]);
}