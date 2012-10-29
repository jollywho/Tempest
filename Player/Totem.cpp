#include "Totem.h"
#include "Engine/SpriteResource.h"

Totem::Totem(int ux, int uy, int sx, int sy)
{
	mpInner = &SpriteResource::RequestResource("Player", "TotemInner.png");
	mpOuter = &SpriteResource::RequestResource("Player", "Totem.png");

	mShift.x = sx - mpOuter->width/2; mShift.y = sy - mpOuter->height/2;
	mUnshift.x = ux - mpOuter->width/2; mUnshift.y = uy - mpOuter->height/2;

	mClip = 0;
	mClipTimer.Start();
	mPull = false;
	mUnset = true;
}

Totem::~Totem()
{
	//cleanup
}

void Totem::ReleaseTotems()
{
	mPull = false;
	mTarget = mUnshift;
}

void Totem::PullTotems()
{
	mPull = true;
	mTarget = mShift;
}

void Totem::Update(const int& rDeltaTime, int x, int y, bool isAnimated)
{
	if (mUnset) { mX = x; mY = y; mUnset = false; }
	if (isAnimated) Shared::CheckClip(mClipTimer, mClip, mpInner->interval, mpInner->maxClips, 0);

	float dx = (mTarget.x) - (mX) + x;
    float dy = (mTarget.y) - (mY) + y;
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));

	float spd = Length * 5;
	
	float xa = dx / Length;
	float ya = dy / Length;
	mX += (xa * (spd * (rDeltaTime / 1000.f)));
	mY += (ya * (spd * (rDeltaTime / 1000.f)));
	
}

void Totem::Draw(SDL_Surface *pDest)
{
	Shared::DrawSurface(mX+15, mY+5, mpInner->pSurface, pDest, &mpInner->pClips[mClip]);
    Shared::DrawSurface(mX, mY, mpOuter->pSurface, pDest);
}

float Totem::GetMiddle()
{
    return mX + mpOuter->width/2;
}

float Totem::GetVertical()
{
    return mY;
}