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
#pragma once
#ifndef ATTACK_H
#define ATTACK_H

#include "Action.h"

class Attack : public Action
{
private:
	std::string mBulletId;
	int mSpeed;
	double mRot;
	std::string mSpriteId;
	int mInterval;
	Timer mTimer;
	int mCount;
public:
	Attack(bool del, std::string bullet_id, int speed, int rot, int interval);
	~Attack();
	void Update(Enemy& enemy, Uint32 delta_ticks);
};


#endif

