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
#ifndef ACTION_H
#define ACTION_H

#include "Engine/Shared.h"

class Enemy;

class Action
{
public:
	Action();
	Action(bool del, int loops);
	virtual ~Action(){};
	virtual void Update(Enemy& enemy, Uint32 delta_ticks) {};
	inline bool RequestNext() { 
		mLoops != -1 && mLoops > 0 ? mLoops--, mNext = true : 0; 
		return mNext;};
	bool RequestDelete() {return mDel;};
	bool IsLoopAction() {return mLoops > 0 ? 1 : 0;};
	int ActionCount() {return mLoops;};
protected:
	bool mNext;
	bool mDel; //one-time-only actions
	int mLoops;
};


#endif

