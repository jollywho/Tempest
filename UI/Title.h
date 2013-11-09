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
#ifndef TITLE_H
#define TITLE_H

#include "Engine/Shared.h"
#include "Engine/NFont.h"

struct SpriteInfo;

//this is a member of Level base and should be called
//		at the start of a level and before a boss is spawned.
class Title
{
private:
	struct FadeChar
	{
		int fade;
		char ch[2];
	} mChars[50];
	int mLength;
	int mMaxLength;
	bool mStart;
	bool mDone;
	Point mPos;
	Timer mTimer;
	Timer mFinTimer;
	NFont mpFont[5];
	SDL_Surface* mspSurfaceFade[5];
public:
    Title(const char* title);
    ~Title();
	void Start() { mStart = true; mLength = 0; }
    void Update(const int& rDeltaTime);
    void Draw(SDL_Surface *pdest);
};

#endif