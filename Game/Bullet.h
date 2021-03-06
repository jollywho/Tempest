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
��*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Engine/Shared.h"

class Bullet
{
public:
    Bullet(int clip, bool del, bool explode) : mClip(clip), mDelete(del), mExplode(explode){};
    virtual void Update(const int& rDeltaTime) = 0;
    virtual void Draw(SDL_Surface *pdest) = 0;

    bool RequestDelete() {return mDelete;}
protected:
	bool mExplode;
	bool mDelete;
    int mClip;
    Timer mClipTimer;
};

#endif