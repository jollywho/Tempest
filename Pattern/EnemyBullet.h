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
#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "Game/Bullet.h"

struct SpriteInfo;
struct RotationInfo;

class EnemyBullet : public Bullet
{
public:
	EnemyBullet(std::string id, float x, float y, int angle, int ch_time = 0, float xmod = 1, float ymod = 1, int angle2 = 0);
	~EnemyBullet();
    void DetectCollision();
    void Destroy();
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface *pdest);

	bool IsCollision(HitBox& obj);
private:
	static const int TOO_FAR = 50;
	int mChangeTime;
	RotationInfo* mpRotInfo;
	static SpriteInfo* mspExpInfo;
    float xvel, yvel;
    float mX, mY;
	float mModx; float mMody;
	int mAngle; int mAngle2;
	void CheckBounds();
};

#endif