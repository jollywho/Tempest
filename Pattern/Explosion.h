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
private:
	SpriteInfo* info;
	int clip;
	int detTime;
	Timer clip_Timer;
	int altInterval;
	float xVal; float yVal;
	float xVel; float yVel;
	bool started;
	bool m_delete;
	static std::map<std::string, std::list<ExplosionInfo>> explosions;
public:
	Explosion(int x, int y, int xv, int yv, ExplosionInfo nfo);
    static void ClearList();
    void Update(Uint32 delta_ticks);
    void Draw(SDL_Surface *dest);
	bool RequestDelete() { return m_delete; };
	static void AddExplosionInfo(std::string expId, std::string spriteId, int magnitude, 
		int delay, int offsetX=0, int offsetY=0, bool residue=false);
	static void RequestExplosion(std::string expId, int x, int y, int xv, int yv);
};


#endif

