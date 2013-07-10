#include "Totem.h"
#include "Engine/SpriteResource.h"
#include "UI/NSprite.h"
#include "State/Playstate.h"
#include "Engine/SFX.h"

Totem::Totem(int ux, int uy, int sx, int sy)
{
	mpInner = &SpriteResource::RequestResource("Player", "totem_inner");
	mpOuter = &SpriteResource::RequestResource("Player", "totem");
	mpFlash = new NSprite(ux, uy, &SpriteResource::RequestResource("Player", "totem_flash"), true, false);

	mShift.x = sx - mpOuter->width/2; mShift.y = sy - mpOuter->height/2;
	mUnshift.x = ux - mpOuter->width/2; mUnshift.y = uy - mpOuter->height/2;

	mHealth = 50;
	mClip = 0;
	mClipTimer.Start();
	mPull = false;
	mUnset = true;
	mDet = false; mDisable = false;
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
	if (mDisable) return;
	
	if (mUnset) { mX = x; mY = y; mUnset = false; }
	if (isAnimated) Shared::CheckClip(mClipTimer, mClip, mpInner->interval, mpInner->maxClips, 0);

	float dx = (mTarget.x) - (mX) + x;
	float dy = (mTarget.y) - (mY) + y;
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));

	if (mDetTimer.GetTicks() > 600) 
	{ 
		mDisable = true;  
		CPlayState::Instance()->mpPlayer->Knockback(dx,dy,SPEED*50);
		 // + request explosion
		 return;
	}

	float spd = Length * SPEED;
	
	float xa = dx / Length;
	float ya = dy / Length;

	if (!mpFlash->IsDone()) 
	{ 
		mpFlash->SetPos(FPoint(mX + mpOuter->width/2, mY + mpOuter->height/2)); 
		mpFlash->Update(); 
		ya = 1;
		spd = 100;
	}

	mX += (xa * (spd * (rDeltaTime / 1000.f)));
	mY += (ya * (spd * (rDeltaTime / 1000.f)));
}

void Totem::Draw(SDL_Surface *pDest)
{
	if (mDisable) return;

	Shared::DrawSurface(mX+15, mY+5, mpInner->pSurface, pDest, &mpInner->pClips[mClip]);
    Shared::DrawSurface(mX, mY, mpOuter->pSurface, pDest);
	mpFlash->Draw(pDest);
}

float Totem::GetMiddle()
{
    return mX + mpOuter->width/2;
}

float Totem::GetVertical()
{
    return mY;
}

SDL_Rect Totem::GetBounds()
{
	SDL_Rect temp = { mX, mY, mpOuter->width, mpOuter->height };
	return !mDisable ? temp : SDL_Rect();
}

void Totem::ResetPos(int x, int y)
{
	mX = x;
	mY = y;
}

void Totem::TakeHit()
{
	mpFlash->Reset();
	CPlayState::Instance()->mpPlayer->Knockback(0,1,200);
	if (mHealth < 1) {
		mDet = true;
		mDetTimer.Start();
		//SFX::PlaySoundResource("totem_det");
		}
	else 
		mHealth--;
}