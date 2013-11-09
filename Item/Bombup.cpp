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
#include "Bombup.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "Game/GameScore.h"
#include "Game/Camera.h"
#include "Player/Player.h"

Bombup::Bombup(int x, int y, int value) : Item(x, y, value, "bombup")
{
	mpPickup = &SpriteResource::RequestResource("Item", "bombup_received");
	mAir = true;
    mDelete = false;
	yvel = 200 * ((rand() % 2) == 1 ? -1 : 1);
	xvel = 200 * ((rand() % 2) == 1 ? -1 : 1);
}

Bombup::~Bombup() 
{
}

void Bombup::Update(Uint32 delta_ticks)
{
	if (pickedup)
	{
		Shared::CheckClip(mClipTimer, mClip, mpPickup->interval, mpPickup->maxClips, mpPickup->maxClips-1);
		if (!received) 
		{
			SFX::PlaySoundResource("bombup_pickup");
			received = true;
			mDurationTimer.Start(); 
			GameScore::Instance()->IncreaseBombups();
			yvel = -100;
			xvel = 0;
		}
		if (mDurationTimer.GetTicks() > 1000)
			mDelete = true;
	}
	else 
	{
		Shared::CheckClip(mClipTimer, mClip, 50, mpInfo->maxClips, 0);
		CheckCollision();
		CheckWallCollision(mpInfo->width, mpInfo->height);
	}
	
	mX += (xvel * (delta_ticks / 1000.f));
	mY += (yvel * (delta_ticks / 1000.f));

	mOffset.x = mX;
    mOffset.y = mY;
}

void Bombup::Draw(SDL_Surface *pdest)
{
	if (pickedup) {
		Camera::Instance()->DrawSurface(mOffset.x - 50, mOffset.y + Camera::Instance()->CameraY2() - 25,
			smpPickupFrameInfo, pdest, NULL);
		Camera::Instance()->DrawSurface(mOffset.x, mOffset.y + Camera::Instance()->CameraY2(),
			mpPickup->pSurface, pdest, &mpPickup->pClips[mClip]);
	}
	else
		Camera::Instance()->DrawSurface(mOffset.x, mOffset.y + Camera::Instance()->CameraY2(),
			mpInfo->pSurface, pdest, &mpInfo->pClips[mClip]);
}