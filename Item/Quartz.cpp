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
#include "Quartz.h"
#include "Engine/SpriteResource.h"
#include "UI/Interface.h"
#include "Game/Gamescore.h"
#include "Game/Camera.h"
#include "State/playstate.h"
#include "Player/Player.h"
#include "UI/ScoreMSG.h"

Quartz::Quartz(int x, int y, int value) : Item(x, y, 1000, "quartz")
{
	mAir = false;
    mDelete = false;
	mLockedOn = false;
	mClip = 0;
}

Quartz::~Quartz() 
{
	if (pickedup)
	{
		GameScore::Instance()->IncreaseQuartzCount();
		CPlayState::Instance()->score_list.push_back(new ScoreMSG(mX, mY - Camera::Instance()->CameraY2(), mSpawnSide, GameScore::Instance()->GetBonus() * val));
	}
}

void Quartz::Update(Uint32 delta_ticks)
{
	if (pickedup) mDelete = true;
	Shared::CheckClip(mClipTimer, mClip, 50, mpInfo->maxClips, 0);
	SDL_Rect playerbox = CPlayState::Instance()->mpPlayer->GetOuterBounds().rect;
    float dx = (playerbox.x + playerbox.w / 2) - (mOffset.x - Camera::Instance()->CameraX()  + mOffset.w / 2);
    float dy = (playerbox.y + playerbox.h / 2) - (mOffset.y - Camera::Instance()->CameraY2() + mOffset.h / 2);
	double length = sqrt(pow(dx, 2) + pow(dy, 2));

	if (length > 0.1f && length < 100 && mDurationTimer.GetTicks() > 600 && !mLockedOn)
	{
		mLockedOn = true;
		mAccelTimer.Start();
	}

	if (mLockedOn)
	{
		float xa = dx / length;
		float ya = dy / length;
		yvel += mAccelTimer.GetTicks() / 50;
		mX += (xa * (yvel * (delta_ticks / 1000.f)));
		mY += (ya * (yvel * (delta_ticks / 1000.f)));
		CheckCollision();
	}
	else
	{
		mY += (yvel * (delta_ticks / 1000.f));
	}
	mOffset.x = mX;
    mOffset.y = mY;

    
	if (CheckOffscreen(mX, mY - Camera::Instance()->CameraY2(), mpInfo->height))
		mDelete = true;
}

void Quartz::Draw(SDL_Surface *pdest)
{
    Camera::Instance()->DrawSurface(mOffset.x, mOffset.y,
        mpInfo->pSurface, pdest, &mpInfo->pClips[mClip]);
}