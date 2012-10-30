#include "Layer.h"
#include "Game/Camera.h"

Layer::Layer(SDL_Surface* pSrc, int height, int startPos)
{
	printf("Layer Created!\n");
	mpSurface = pSrc;
	mHeight = height;
	mStartY = startPos;
	mOffset = 0;
	mY = 0; mY2 = mY - height;
	mFixed = false; mDone = false;
	mStarted = false;
}

Layer::Layer(SDL_Surface* pSrc, int height, int startPos, int horizontalOffset)
{
	printf("Layer Created!\n");
	mpSurface = pSrc;
	mHeight = height;
	mStartY = startPos;
	mOffset = horizontalOffset;
	mY = 0; mY2 = mY - height;
	mFixed = true; mDone = false;
	mStarted = false;
}

Layer::~Layer()
{
    printf("Layer Deleted\n");
}

void Layer::Start()
{
	if (!mStarted)
	{
		mStarted = true;
	}
}

void Layer::Update(Uint32 deltaTicks, float spd)
{
	if (mDone) return;
	
	if (mStarted)
	{
		mY += spd;
		mY2 += spd;
		if (mY >= GAME_BOUNDS_HEIGHT)
			mY = mY2-mHeight;
		if (mY2 >= GAME_BOUNDS_HEIGHT)
			mY2 = mY-mHeight;
		mBounds.y = 0;
		mBounds.x = (int)Camera::CameraX();
	}
	if (Camera::CameraY() >= mStartY && !mFixed) Start();
}

void Layer::Draw(SDL_Surface *pDest)
{
	if (mDone || !mStarted) return;
	if (!mFixed)
	{
	Shared::DrawSurface(GAME_BANNER_WIDTH, (int)mY, mpSurface, pDest, &mBounds);
	Shared::DrawSurface(GAME_BANNER_WIDTH, (int)mY2, mpSurface, pDest, &mBounds);
	}
	else
	{
	Shared::DrawSurface(GAME_BANNER_WIDTH + mOffset, (int)mY, mpSurface, pDest, NULL);
	Shared::DrawSurface(GAME_BANNER_WIDTH + mOffset, (int)mY2, mpSurface, pDest, NULL);
	}
}