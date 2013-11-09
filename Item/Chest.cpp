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
#include "Chest.h"
#include "Gem.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "UI/Interface.h"
#include "Player/Player.h"
#include "Game/GameScore.h"
#include "Game/Camera.h"

Chest::Chest(int x, int y, int value) : Item(x, y, value, "Chest")
{
	mAir = false;
    mDelete = false;
	opened = false;
	mClip = 0;
	spawnCount = 0;
}

Chest::~Chest() 
{
}

void Chest::Update(Uint32 delta_ticks)
{
	CheckCollision();
	if (pickedup)
	{
		Shared::CheckClip(mClipTimer, mClip, 50, mpInfo->maxClips, mpInfo->maxClips-1);

		if (mClip == mpInfo->maxClips-1 && !opened) 
		{ 
			opened = true;
			spawn_Timer.Start();
		}

		if (spawnCount < 10 && spawn_Timer.GetTicks() > 100)
		{
			spawn_Timer.Start();
			CPlayState::Instance()->item_list.push_back(new Gem(mX + mpInfo->width/2, mY, 825));
			spawnCount++;
		}
	}
    
	//if (CheckOffscreen(mX, mY + Camera::Instance()->CameraY2, mpInfo->height))
	//	mDelete = true;
}

void Chest::Draw(SDL_Surface *pdest)
{
    Camera::Instance()->DrawSurface(mOffset.x, mOffset.y,
        mpInfo->pSurface, pdest, &mpInfo->pClips[mClip]);
}