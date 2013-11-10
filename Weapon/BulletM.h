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
#ifndef BULLETM
#define BULLETM
#include "PlayerBullet.h"
#include <string>

struct RotationInfo;
struct SpriteInfo;

class BulletM : public PlayerBullet
{
public:
	BulletM(float x, float y, int angl, int rots);
	~BulletM() {}

	static void Init(std::string id, std::string expId);

	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface *pdest);
private:
	static RotationInfo* mpInfo;
	static SpriteInfo* _expInfo;
};

#endif