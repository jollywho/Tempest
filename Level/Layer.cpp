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
#include "Layer.h"
#include "Game/Camera.h"

Layer::Layer(SDL_Surface* pSrc, int height, int startPos)
{
	printf("Layer Created!\n");
	mpSurface = pSrc;
	mHeight = height;
	mStartY = startPos;
	mOffset = 0;
	mY = 0; mY2 = mY - height;
	mFixed = false; mDone = false;
	mStarted = false;
}

Layer::Layer(SDL_Surface* pSrc, int height, int startPos, int horizontalOffset)
{
	printf("Layer Created!\n");
	mpSurface = pSrc;
	mHeight = height;
	mStartY = startPos;
	mOffset = horizontalOffset;
	mY = 0; mY2 = mY - height;
	mFixed = true; mDone = false;
	mStarted = false;
}

Layer::~Layer()
{
    printf("Layer Deleted\n");
}

void Layer::Start()
{
	if (!mStarted)
	{
		mStarted = true;
	}
}

void Layer::Update(Uint32 delta_ticks, float spd)
{
	if (mDone) return;
	
	if (mStarted)
	{
		mY += spd;
		mY2 += spd;
		if (mY >= GAME_BOUNDS_HEIGHT)
			mY = mY2-mHeight;
		if (mY2 >= GAME_BOUNDS_HEIGHT)
			mY2 = mY-mHeight;
		mBounds.y = 0;
		mBounds.x = (int)Camera::Instance()->CameraX();
	}
	if (Camera::Instance()->CameraY() >= mStartY && !mFixed) Start();
}

void Layer::Draw(SDL_Surface *pdest)
{
	if (mDone || !mStarted) return;
	if (!mFixed)
	{
	Shared::DrawSurface(GAME_BANNER_WIDTH, (int)mY, mpSurface, pdest, &mBounds);
	Shared::DrawSurface(GAME_BANNER_WIDTH, (int)mY2, mpSurface, pdest, &mBounds);
	}
	else
	{
	Shared::DrawSurface(GAME_BANNER_WIDTH + mOffset, (int)mY, mpSurface, pdest, NULL);
	Shared::DrawSurface(GAME_BANNER_WIDTH + mOffset, (int)mY2, mpSurface, pdest, NULL);
	}
}