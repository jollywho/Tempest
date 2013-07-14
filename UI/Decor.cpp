#include "Decor.h"
#include "Engine/SpriteResource.h"

Decor::Decor()
{
	mpInfo = &SpriteResource::RequestResource("UI", "decor");
	mX = rand() % WINDOW_WIDTH;
	mY = rand() % WINDOW_WIDTH;
	
	mClip = rand() % mpInfo->maxClips-1;
	if (mClip == 0) show = true;
	else show = false;
	mClipTimer.Start();
}

void Decor::Update(int deltaTicks)
{
	Shared::CheckClip(mClipTimer, mClip, mpInfo->interval + rand() % 50, mpInfo->maxClips, 0);
	if (mClip >= mpInfo->maxClips-1)
	{
		mX = rand() % WINDOW_WIDTH;
		mY = rand() % WINDOW_WIDTH;
		mClip = rand() % 2;
		if (mClip == 0) show = true;
		else show = false;
	}
	mY += 50 * (deltaTicks/1000.f);
}

void Decor::Draw(SDL_Surface *pDest)
{
	if (show)
		Shared::DrawSurface(mX, mY, mpInfo->pSurface, pDest, &mpInfo->pClips[mClip]);
}