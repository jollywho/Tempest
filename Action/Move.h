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
#ifndef MOVE_H
#define MOVE_H

#include "Action.h"

enum Moves
{
	MV_STRAIGHT,
	MV_DIAG,
	MV_CURVE
};

enum Direction
{
	UP = 	1, 
	DOWN =	2, 
	left =	3, 
	right =	4,
};

class Move : public Action
{
private:
	int mDestx;
	int mDesty;
	int mSpeed;
	Moves mMoveType;
	Timer mTimer;
	Direction mDir;
	int mAngle;
public:
	Move(bool del, int move_type, int speed, int dest_x, int dest_y, int dir_type);
	~Move();
	void Update(Enemy& enemy, Uint32 delta_ticks);
	bool Straight(Enemy& enemy, Uint32 delta_ticks);
};


#endif

