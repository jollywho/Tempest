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
#ifndef ZOWN_H
#define ZOWN_H

#include "Enemy.h"

class Zown : public Enemy
{
	REGISTER(Zown);
private:
    Timer mAtkTimer;
    double mRot;
	int mAtkCount;
public:
    explicit Zown(int x, int y, std::list<Action*>& actions);
    ~Zown();
    void Attack();
    void Update(Uint32 delta_ticks);
    void Draw(SDL_Surface *pdest);
    static void Init();
    static void Cleanup();
    void TakeHit(int dmg);
};


#endif