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
#ifndef MTYPE_H
#define MTYPE_H

#include "Weapon.h"

struct SpriteInfo;
class NSprite;

class MType : public Weapon 
{
public:
	MType();
	~MType();
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface *pdest);
	void MajorAttack(std::list<PlayerBullet*>& pl_bulletlist);
	void MinorAttack(std::list<PlayerBullet*>& pl_bulletlist);
	void SetPos(int x, int y, int mv);
	void ResetPos(int x, int y);
	void StopAttack();
	void Shift();
	void Unshift();

	bool TakeHit();
private:
	SpriteInfo* mpShotAnim;
	NSprite* mpSlash;
	int mShotAnimClip;
	Timer mShotAnimTimer;
	float mov;
	Point wpn_pos;
};

#endif