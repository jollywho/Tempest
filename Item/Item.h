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
#ifndef ITEM_H
#define ITEM_H

#include "Engine/Shared.h"
#include "Engine/SFX.h"

struct SpriteInfo;

class Item
{
public:
    Item(int x, int y, int value, char* id);
    virtual ~Item();
    static void Init();
    static void Cleanup();
    bool mDelete;
    bool RequestDelete() {return mDelete;};
	virtual void Update(Uint32 delta_ticks){};
	virtual void Draw(SDL_Surface *pdest){};
    void CheckCollision();
	void CheckWallCollision(double w, double h);
	bool CheckOffscreen(double x, double y, double h);
	static void SetBonus(int val);
	bool Air() {return mAir;}
protected:
    int mClip;
    SDL_Rect mOffset;
    Timer mClipTimer;
	Timer mDurationTimer;
    float mX; float mY;
    float xvel; float yvel;
	bool pickedup; bool received;
    int val;
	bool mAir;
	SpriteInfo* mpInfo;
	int mSpawnSide;
	static SDL_Surface* smpPickupFrameInfo;
};

#endif

