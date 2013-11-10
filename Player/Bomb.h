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
#ifndef BOMB_B
#define BOMB_B

#include "Engine/Shared.h"

struct SpriteInfo;

class Bomb
{
public:
    Bomb();
    ~Bomb();
    void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* dest);
	void Start(int x, int y);
	void BulletWipe();

	bool IsActive() {return mActive;};
private:
    Timer dps_timer;
	Timer mClipTimer;
	bool mActive;
	static SpriteInfo* mpSprite;
	int mClip;
	int mX; int mY;
};

#endif