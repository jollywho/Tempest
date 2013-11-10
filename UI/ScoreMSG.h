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
#ifndef SCOREMSG_H
#define SCOREMSG_H

#include <sstream>
#include "Engine/NFont.h"
#include "Engine/Shared.h"

class ScoreMSG
{
public:
    ScoreMSG(int x, int y, int xDir, int value);
    ~ScoreMSG();  

    static void Init();
    static void Cleanup();
  
    void Update(Uint32 delta_ticks);
    void Draw(SDL_Surface *pdest);

	bool RequestDelete() {return mDelete;};
private:
	static Timer msTallyTimer;
	static int msTallyTotal;
	static int msExtend;
    Timer mDurationTimer;
    float mX; float mY;
    float xvel; float yvel;
	int mValue;
	std::ostringstream mMsg;
	static SDL_Surface* mspSurfaceFade[4];
	static NFont msFontFade[4];
	int mClip;
	bool mDelete;
	Timer mClipTimer;
};

#endif

