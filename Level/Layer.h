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
#ifndef LAYER_H
#define LAYER_H

#include "Engine/Shared.h"

class Layer
{
public:
    Layer(SDL_Surface* src, int height, int startPos);
	Layer(SDL_Surface* src, int height, int startPos, int xoffset);
    ~Layer();
    void Draw(SDL_Surface *pdest);
	void Update(Uint32 delta_ticks, float spd);
	void Start();
	bool IsDone() { return mDone; }
private:
	SDL_Rect mBounds;
    SDL_Surface* mpSurface;
	float mY; float mY2;
	int mStartY;
	int mHeight; int mOffset;
	bool mFixed; 
	bool mDone; 
	bool mStarted;
};

#endif