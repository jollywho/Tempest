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
#include "Attack.h"
#include "Enemy/Enemy.h"
#include "State/PlayState.h"
#include "Pattern/EnemyBullet.h"

Attack::Attack(bool del, std::string bullet_id, int speed, int rot, int interval)
	: Action (del, -1)
{
	mBulletId = bullet_id;
	mSpeed = speed;
	mRot = rot;
	mInterval = interval;
	mTimer.Start();
	mCount = 2;
}

Attack::~Attack()
{

}

void Attack::Update(Enemy& enemy, Uint32 delta_ticks)
{
	if (mTimer.GetTicks() > mInterval)
	{
		mTimer.Start();
		SDL_Rect rec = enemy.GetBounds();
		rec.x += rec.w/2;
		rec.y += rec.h/2;
		CPlayState::Instance()->en_bulletlist.push_back(new EnemyBullet(mBulletId, rec.x, rec.y, mRot));
		--mCount;
	}
	mNext = mCount <= 0;
}