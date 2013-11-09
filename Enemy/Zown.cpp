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
#include "Zown.h"
#include "Engine/SpriteResource.h"
#include "Game/Camera.h"
#include "Pattern/Explosion.h"
#include "Engine/Engine.h"

REGISTERIMPL(Zown);

Zown::Zown(int x, int y, std::list<Action*>& actions) : Enemy("zown", x, y, actions)
{
	mHealth = 50;
	mMaxHealth = 50;
	mAir = true;
    mRot = 0; mAtkCount = 0;
	mAtkTimer.Start();
	mVel = Point(0,0);
}

Zown::~Zown()
{
    if (mHit)
        SDL_FreeSurface(mpCopySurface);
}

void Zown::TakeHit(int dmg)
{
    mHealth -= dmg;
    FlashRed(mpInfo->pSurface, &mpInfo->pClips[mClip]);
}

void Zown::Init()
{
	printf("Zown initialize\n");
}

void Zown::Cleanup()
{

}

void Zown::Attack()
{
	//CPlayState::Instance()->en_bulletlist.push_back(new ERotBullet(mX + mpInfo->width/2, mY + mpInfo->height, 0, "Arrow.png"));
	mAtkTimer.Start();


	mAtkCount++;
	
	if (mAtkCount > 3) mAtkCount = 1;

	mRot += .4;
	if (mRot > M_PI)
		mRot = 0;
	
	/*
	for (double i=0-rot; i<=M_PI/2+rot - .4; i+= .4 )
    {
        double x = cos(i);
        double y = sin(i);
        CPlayState::Instance()->en_bulletlist.push_back(new ERotBullet(atkgatset.x + GATE_WIDTH/2,
			atkgateLE.y + GATE_WIDTH/2,
			x*100, y * 100, "LargeRed.png"));

		CPlayState::Instance()->en_bulletlist.push_back(new ERotBullet(atkgateRIt.x + GATE_WIDTH/2,
			atkgateRIGHset.y + GATE_WIDTH/2,
			-x*100, y * 100, "LargeRed.png"));
    }
	*/
    mAtkTimer.Start();

}

void Zown::Update(Uint32 delta_ticks)
{
	Decide(delta_ticks);
	if (Explode(true)) return;
	if (CheckHealth()) return;
	DetectCollision();

    if (mAtkTimer.GetTicks() > 480)
        Attack();
	Shared::CheckClip(mClipTimer, mClip, mpInfo->interval, mpInfo->maxClips, 0);

    mHitbox.x = mPos.x;
    mHitbox.y = mPos.y;
}

void Zown::Draw(SDL_Surface *pdest)
{
	if (mExplode) return;

    if (mHit)
        Camera::Instance()->DrawSurface(mHitbox.x, mHitbox.y,
            mpCopySurface, pdest, &mpInfo->pClips[mClip]);
    else
        Camera::Instance()->DrawSurface(mHitbox.x, mHitbox.y,
            mpInfo->pSurface, pdest, &mpInfo->pClips[mClip]);
}