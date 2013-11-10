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
#include "Gem.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "UI/Interface.h"
#include "Game/Camera.h"
#include "Player/Player.h"
#include "Game/GameScore.h"
#include "UI/ScoreMsg.h"

Gem::Gem(int x, int y, int value, bool autoLocked) : Item(x, y, value, "gem")
{
	mAir = true;
    mDelete = false;
	yvel = -200;
	mLockedOn = autoLocked;
	mClip = 0;
	mAccelTimer.Start();
}

Gem::~Gem() 
{
	if (pickedup)
	{
		GameScore::Instance()->IncreaseGemCount();
		GameScore::Instance()->IncreaseBonus();
		SFX::PlaySoundResource("gem_pickup");
		//CPlayState::Instance()->scoreMsgList.push_back(new ScoreMSG(mX, mY, mSpawnSide, GameScore::Instance()->GetBonus() * val));
		CPlayState::Instance()->score_list.push_back(new ScoreMSG(mX, mY, mSpawnSide, val));
	}
}

void Gem::Update(Uint32 delta_ticks)
{
	if (pickedup) mDelete = true;
	Shared::CheckClip(mClipTimer, mClip, 50, mpInfo->maxClips, 0);

	SDL_Rect playerbox = CPlayState::Instance()->mpPlayer->GetOuterBounds().rect;
    float dx = (playerbox.x + playerbox.w / 2) - (mOffset.x - Camera::Instance()->CameraX()  + mOffset.w / 2);
    float dy = (playerbox.y + playerbox.h / 2) - (mOffset.y + mOffset.h / 2);
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));

	if (Length > 0.1f && Length < 200 && !mLockedOn)
	{
		mLockedOn = true;
		mAccelTimer.Start();
	}

	if (CPlayState::Instance()->mpPlayer->IsExploding())
		mLockedOn = false;

	if ((mLockedOn) && mDurationTimer.GetTicks() > 600)
	{
		float xa = dx / Length;
		float ya = dy / Length;
		yvel += mAccelTimer.GetTicks() / 50;
		mX += (xa * (yvel * (delta_ticks / 1000.f)));
		mY += (ya * (yvel * (delta_ticks / 1000.f)));
		CheckCollision();
	}
	else
	{
		if (mDurationTimer.GetTicks() > 200) yvel += 500 * delta_ticks / 1000.f;
		mY += (yvel * (delta_ticks / 1000.f));
	}
	mOffset.x = mX;
    mOffset.y = mY;

    
	if (CheckOffscreen(mX, mY, mpInfo->height))
		mDelete = true;
}

void Gem::Draw(SDL_Surface *pdest)
{
    Camera::Instance()->DrawSurface(mOffset.x, mOffset.y + Camera::Instance()->CameraY2(),
        mpInfo->pSurface, pdest, &mpInfo->pClips[mClip]);
}