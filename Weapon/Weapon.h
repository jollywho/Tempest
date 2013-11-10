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
#ifndef WEAPON_H
#define WEAPON_H

#include "Engine/Shared.h"
#include "PlayerBullet.h"
#include <vector>
#include <list>

class Totem;

enum WeaponType
{
	M_type,
	S_type,
	R_type,
};

class Weapon 
{
public:
	inline void LevelUp() { if (level < MAX_TOTEMS) level++;}
	virtual void Update(const int& rDeltaTime) = 0;
	virtual void Draw(SDL_Surface *pdest) = 0;
	virtual void MajorAttack(std::list<PlayerBullet*>& pl_bulletlist) = 0;
	virtual void MinorAttack(std::list<PlayerBullet*>& pl_bulletlist) = 0;
	virtual void StopAttack() = 0;
	virtual void Shift() = 0;
	virtual void Unshift() = 0;
	virtual void SetPos(int x, int y, int mv) = 0;
	virtual void ResetPos(int x, int y) = 0;
	virtual bool TakeHit() = 0;
protected:
	Timer wpn_timer;
	int minor_speed;
	int major_speed;
	bool is_shift;
	int level;
	int mHealth;
	int rot_divs;
	std::vector<Totem*> totem_list;
};

#endif