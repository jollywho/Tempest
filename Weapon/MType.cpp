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
#include "MType.h"
#include "Engine/SpriteResource.h"
#include "Engine/SFX.h"
#include "State/playstate.h"
#include "Player/Player.h"
#include "Player/Totem.h"
//#include "Beam.h"
#include "PlayerBullet.h"
#include "UI/NSprite.h"

MType::MType()
{
	printf("MType Crated\n");
	wpn_timer.Start();
	level = MAX_TOTEMS;
	mHealth = 200;
	mpSlash = new NSprite(0,0, &SpriteResource::RequestResource("Player", "slash"), true);
	totem_list.push_back(new Totem(40,90, -40,-50));
	totem_list.push_back(new Totem(-40,90,-40,-50));
	totem_list.push_back(new Totem(80,80, -40,-50));
	totem_list.push_back(new Totem(-80,80,-40,-50));
	mpShotAnim = &SpriteResource::RequestResource("Player", "shot");
	rot_divs = 2;
	PlayerBullet::Init("m_type", "conc_explode");
	minor_speed = 90; major_speed = 90;
	mShotAnimClip = 0;
	mov = 0;
}

MType::~MType()
{
	printf("MType Deleted\n");
	for (auto it = totem_list.begin(); it != totem_list.end(); it++)
		delete (*it);
	delete mpSlash;
}

void MType::SetPos(int x, int y, int mv)
{
	mov = mv;
	wpn_pos.x = x; wpn_pos.y = y;
}

void MType::ResetPos(int x, int y) 
{
	wpn_pos.x = x; wpn_pos.y = y;
    for (auto it = totem_list.begin(); it != totem_list.end(); it++)
		(*it)->ResetPos(x, y);
}

void MType::MinorAttack(std::list<PlayerBullet*>& pl_bulletlist) 
{		
	if (!mpSlash->IsDone()) return;
	if (wpn_timer.GetTicks() > minor_speed  || wpn_timer.IsPaused())
	{
		wpn_timer.Start(); 	mShotAnimClip = 0; mShotAnimTimer.Start();
		SFX::PlaySoundResource("attack");
		
		pl_bulletlist.push_back(new PlayerBullet(wpn_pos.x, wpn_pos.y, 180+mov, rot_divs));
		for (auto it = totem_list.begin(); it != totem_list.end(); it++)
		{
			if (!(*it)->IsDisabled())
			{
				int x = (*it)->GetMiddle();
				int y = (*it)->GetVertical();
				for (int i=4; i<10; i+=2)
				{
					pl_bulletlist.push_back(new PlayerBullet(x+(i*2), y+(i*2), 180+(i*2)+mov,rot_divs));
					pl_bulletlist.push_back(new PlayerBullet(x-(i*2), y+(i*2), 180-(i*2)+mov,rot_divs));
				}
			}
		}
	}
}

void MType::MajorAttack(std::list<PlayerBullet*>& pl_bulletlist) 
{ 						
	if (mpSlash->IsDone())
	{
		SFX::PlaySoundResource("attack");
		mpSlash->Reset();
		SFX::PlaySoundResource("slash");
		SFX::PlaySoundResource("slash_hit");
	}
}

void MType::Shift()
{
	for (auto it = totem_list.begin(); it != totem_list.end(); it++)
    {
        (*it)->PullTotems();
    }
}

void MType::Unshift()
{
	for (auto it = totem_list.begin(); it != totem_list.end(); it++)
    {
        (*it)->ReleaseTotems();
    }
}

void MType::StopAttack()
{ 
	if (!wpn_timer.IsPaused())
		wpn_timer.Pause();
}

bool MType::TakeHit()
{
	--mHealth;
	for (auto it = totem_list.begin(); it != totem_list.end(); it++)
		if (!(*it)->IsDisabled()) { (*it)->TakeHit(); return true; }
	return false;
}

void MType::Update(const int& rDeltaTime)
{
	for (auto it = totem_list.begin(); it != totem_list.end(); it++)
	{
		(*it)->Update(rDeltaTime, wpn_pos.x, wpn_pos.y, !wpn_timer.IsPaused());
    }
	mpSlash->SetPos(Point(wpn_pos.x-12, wpn_pos.y));
	mpSlash->Update();
	Shared::CheckClip(mShotAnimTimer, mShotAnimClip, mpShotAnim->interval, mpShotAnim->maxClips, 0);
}

void MType::Draw(SDL_Surface *pdest)
{
	mpSlash->Draw(pdest);
	for (auto it = totem_list.begin(); it != totem_list.end(); it++)
	{
		if (!(*it)->IsDisabled())
		{
			if (!wpn_timer.IsPaused())
				Shared::DrawSurface((*it)->GetMiddle() - mpShotAnim->width/2, (*it)->GetVertical() - mpShotAnim->height/4,
					mpShotAnim->pSurface, pdest, &mpShotAnim->pClips[mShotAnimClip]);
			(*it)->Draw(pdest);
		}
    }
	if (!wpn_timer.IsPaused())
		Shared::DrawSurface(wpn_pos.x - mpShotAnim->width/2, wpn_pos.y - mpShotAnim->height/2,
			mpShotAnim->pSurface, pdest, &mpShotAnim->pClips[mShotAnimClip]);
}