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
#include "Move.h"
#include "Enemy/Enemy.h"
#include "State/PlayState.h"

Move::Move(bool del, int move_type, int speed, int dest_x, int dest_y, int dir_type)
	: Action(del, -1)
{
	mMoveType = (Moves)move_type;
	mSpeed = speed;
	mDestx = dest_x;
	mDesty = dest_y;
	mDir = (Direction)dir_type;
}

Move::~Move()
{

}

void Move::Update(Enemy& enemy, Uint32 delta_ticks)
{
	mNext = Straight(enemy, delta_ticks);
}

bool Move::Straight(Enemy& enemy, Uint32 delta_ticks)
{
	SDL_Rect temp = enemy.GetBounds();
	float dx = (mDestx) - (temp.x);
	float dy = (mDesty) - (temp.y);
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));
	if (Length > 50)
	{
		dx =  dx / Length; dy = dy /Length;
		enemy.Movement(dx * (mSpeed * (delta_ticks/1000.f)), dy * (mSpeed * (delta_ticks/1000.f)));
		return false;
	}
	if (Length < 5) 
		return true;
}