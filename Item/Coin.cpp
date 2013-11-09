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
#include "Coin.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "UI/Interface.h"
#include "Game/Camera.h"
#include "Player/Player.h"
#include "Game/GameScore.h"
#include "UI/ScoreMsg.h"

Coin::Coin(int x, int y, int value) : Item(x, y, value, "coin")
{
	mAir = true;
    mDelete = false;
	yvel = 250;
	mClip = 0;
	mAccelTimer.Start();
}

Coin::~Coin() 
{
	if (pickedup)
	{
		GameScore::Instance()->IncreaseCoinCount();
		GameScore::Instance()->IncreaseBonus();
		SFX::PlaySoundResource("coin_pickup");
		//CPlayState::Instance()->scoreMsgList.push_back(new ScoreMSG(mX, mY, mSpawnSide, GameScore::Instance()->GetBonus() * val));
		CPlayState::Instance()->score_list.push_back(new ScoreMSG(mX, mY, mSpawnSide, val));
	}
}

void Coin::Update(Uint32 delta_ticks)
{
	if (pickedup) mDelete = true;
	Shared::CheckClip(mClipTimer, mClip, 60, mpInfo->maxClips, 0);
	CheckCollision();

	mY += (yvel * (delta_ticks / 1000.f));

	mOffset.x = mX;
    mOffset.y = mY;
    
	if (CheckOffscreen(mX, mY, mpInfo->height))
		mDelete = true;
}

void Coin::Draw(SDL_Surface *pdest)
{
    Camera::Instance()->DrawSurface(mOffset.x, mOffset.y + Camera::Instance()->CameraY2(),
        mpInfo->pSurface, pdest, &mpInfo->pClips[mClip]);
}