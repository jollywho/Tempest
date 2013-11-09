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
#ifndef PLAYERBULLTET_H
#define PLAYERBULLTET_H

#include "Game/Bullet.h"

struct RotationInfo;
struct SpriteInfo;

class PlayerBullet : public Bullet
{
public:
    explicit PlayerBullet(float x, float y, int angle, int rots);
	virtual ~PlayerBullet(){}
	
	static void Init();
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface *pdest);
    static void Init(std::string id, std::string expId);
    void DetectCollision();
	void CheckBounds(Point camera_pos);
private:
	static const int TOO_FAR = 50;
	float xvel, yvel;
    float mX, mY;
    Timer mClipTimer;
	int mAngle;
	int mRots;
	static Point msMinBounds;
	static Point msMaxBounds;
	static RotationInfo* mpInfo;
	static SpriteInfo* _expInfo;
	SDL_Rect mOffset;
};

#endif