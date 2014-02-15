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
#include "Bomb.h"
#include "Engine/SpriteResource.h"
#include "Engine/SFX.h"
#include "Game/Camera.h"
#include "State/Playstate.h"
#include "Pattern/EnemyBullet.h"
#include "Enemy/Enemy.h"
#include "UI/Interface.h"

SpriteInfo* Bomb::mpSprite;

Bomb::Bomb()
{
	printf("Bomb created\n");
	mActive = false;
	mpSprite = &SpriteResource::RequestResource("Player", "bomb");
}

Bomb::~Bomb()
{

}

void Bomb::Start(int x, int y)
{
	if (CPlayState::Instance()->mpInterface->GetBomb() > .8)
	{
		CPlayState::Instance()->mpInterface->SetMaxBomb((mpSprite->interval * mpSprite->maxClips)/60);
		mX = x - mpSprite->width / 2 + Camera::Instance()->CameraX();
		mY = y - mpSprite->height*2 + Camera::Instance()->CameraY2();

		SFX::PlaySoundResource("bomb");
		Camera::Instance()->StartShake(4);

		if (mX < GAME_BANNER_WIDTH)
			mX = GAME_BANNER_WIDTH + 20;
		if (mX + mpSprite->width > GAME_LEVEL_WIDTH)
			mX = GAME_LEVEL_WIDTH - mpSprite->width - 20;

		mActive = true;
		mClip = 0;
		dps_timer.Start();
		mClipTimer.Start();
		mDurTimer.Start();
	}
}

void Bomb::BulletWipe()
{
	for (auto it = CPlayState::Instance()->en_bulletlist.begin(); it != CPlayState::Instance()->en_bulletlist.end(); it++)
        (*it)->Destroy();
}

void Bomb::Update(const int& rDeltaTime)
{
	if (!mActive) return;

	if (mDurTimer.GetTicks() > 60)
	{
		if (!CPlayState::Instance()->mpInterface->SetBomb(-1))
			mActive = false;
		mDurTimer.Start();
	}

	if (mClip == mpSprite->maxClips / 2)
		SFX::PlaySoundResource("bomb2");
	Shared::CheckClip(mClipTimer, mClip, mpSprite->interval, mpSprite->maxClips, mpSprite->maxClips - 1);
	//if (mClip >= mpSprite->maxClips) mActive = false;

	for (auto it = CPlayState::Instance()->en_bulletlist.begin(); it != CPlayState::Instance()->en_bulletlist.end(); it++)
        (*it)->Destroy();

    if (dps_timer.GetTicks() > 60)
    {
        for (auto it = CPlayState::Instance()->enemy_list.begin(); it != CPlayState::Instance()->enemy_list.end();it++)
            (*it)->TakeHit(1);
		dps_timer.Start();
    }
}

void Bomb::Draw(SDL_Surface *pdest)
{
	if (!mActive)
		return;
	Camera::Instance()->DrawSurface(mX, mY, mpSprite->pSurface, pdest, &mpSprite->pClips[mClip]);
}