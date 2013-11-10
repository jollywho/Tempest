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
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Engine/Shared.h"
#include <map>
#include <list>

struct SpriteInfo;
struct ExplosionInfo
{
	std::string spriteId;
	int delay;
	int offsetX;
	int offsetY;
	int magnitude;
	bool residue;
};

class Explosion
{
public:
	Explosion(int x, int y, int xv, int yv, ExplosionInfo nfo);
    void Update(Uint32 delta_ticks);
    void Draw(SDL_Surface *pdest);

	static void ClearList();
	static void AddExplosionInfo(std::string expId, std::string spriteId, int magnitude, 
		int delay, int offsetX= 0, int offsetY = 0, bool residue = false);
	static void RequestExplosion(std::string expId, int x, int y, int xv, int yv);

	bool RequestDelete() {return mDelete;};
private:
	SpriteInfo* mpInfo;
	int mClip;
	int mDetTime;
	Timer mClipTimer;
	int mAltInterval;
	float mX; float mY;
	float mXVel; float mYVel;
	bool mStarted;
	bool mDelete;
	static std::map<std::string, std::list<ExplosionInfo>> msExplosions;
};

#endif

