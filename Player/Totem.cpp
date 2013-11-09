/* Tempest - C++ Danmakufu Game for SDL
*
*  Copyright (C) 2013 Kevin Vollmer.
*  
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*  
ÅÅ*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
#include "Totem.h"
#include "Engine/SpriteResource.h"
#include "UI/NSprite.h"
#include "State/Playstate.h"
#include "Engine/SFX.h"
#include "Pattern/Explosion.h"
#include "Game/Camera.h"

Totem::Totem(int ux, int uy, int sx, int sy)
{
	mpInner = &SpriteResource::RequestResource("Player", "totem_inner");
	mpOuter = &SpriteResource::RequestResource("Player", "totem");
	mpFrame = Shared::LoadImage("Image/Player/totem_frame.png");
	mpHealth = Shared::LoadImage("Image/Player/totem_health.png");
	mpWarning = Shared::LoadImage("Image/Player/totem_warning.png");
	mpFlash = new NSprite(ux, uy, &SpriteResource::RequestResource("Player", "totem_flash"), true, false);

	mShift.x = sx - mpOuter->width/2; mShift.y = sy - mpOuter->height/2;
	mUnshift.x = ux - mpOuter->width/2; mUnshift.y = uy - mpOuter->height/2;
	mHealthBox.x = 0; mHealthBox.y = 0;
	mHealthBox.w = 48; mHealthBox.h = 5;

	mShowHealth = false;
	mHealth = MAX_HEALTH;
	mClip = 0;
	mClipTimer.Start();
	mPull = false;
	mUnset = true;
	mDet = false; mDisable = false;
}

Totem::~Totem()
{
	SDL_FreeSurface(mpFrame);
	SDL_FreeSurface(mpHealth);
	SDL_FreeSurface(mpWarning);
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
		CPlayState::Instance()->mpPlayer->Knockback(dx -x,dy,200);
		Explosion::RequestExplosion("totem", mX + Camera::Instance()->CameraX() + mpOuter->width/2,
			mY + Camera::Instance()->CameraY2() + mpOuter->height/2, 0, 10);
		 return;
	}
	if (mHealthTimer.GetTicks() > 600)
	{
		mHealthTimer.Stop();
		mShowHealth = false;
	}

	float spd = Length * SPEED;
	float xa = dx / Length;
	float ya = dy / Length;

	mpFlash->SetPos(Point(mX + mpOuter->width/2, mY + mpOuter->height/2)); 

	if (!mpFlash->IsDone()) { mpFlash->Update(); }
	if (!mDet)
	{
		mX += (xa * (spd * (rDeltaTime / 1000.f)));
		mY += (ya * (spd * (rDeltaTime / 1000.f)));
	}
}

void Totem::Draw(SDL_Surface *pdest)
{
	Shared::DrawSurface(mX+15, mY+5, mpInner->pSurface, pdest, &mpInner->pClips[mClip]);
    Shared::DrawSurface(mX, mY, mpOuter->pSurface, pdest);
	mpFlash->Draw(pdest);
	if (mShowHealth)
	{
		Shared::DrawSurface(mX+7, mY+5, mpFrame, pdest);
		Shared::DrawSurface(mX+7, mY+5, mpHealth, pdest, &mHealthBox);
		if (mHealth < 10) Shared::DrawSurface(mX+7, mY+5, mpWarning, pdest, &mHealthBox);
	}
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
	return !mDet ? temp : SDL_Rect();
}

void Totem::ResetPos(int x, int y)
{
	mX = x;
	mY = y;
}

void Totem::TakeHit()
{
	mpFlash->Reset();
	if (!mDet)
	{
		CPlayState::Instance()->mpPlayer->Knockback(0,1,30);
		if (mHealth < 1) {
			mDet = true;
			mDetTimer.Start();
			SFX::PlaySoundResource("totem_hit");
			}
		else 
		{
			mHealth--;
			SFX::PlaySoundResource("totem_hit");
		}
	}
	mShowHealth = true;
	mHealthTimer.Start();
	mHealthBox.w = ((float)mHealth / (float)MAX_HEALTH) * MAX_WIDTH;
}