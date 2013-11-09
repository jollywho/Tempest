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
#include "Decor.h"
#include "Engine/SpriteResource.h"

Decor::Decor()
{
	mpInfo = &SpriteResource::RequestResource("UI", "decor");
	mX = rand() % WINDOW_WIDTH;
	mY = rand() % WINDOW_WIDTH;
	
	mClip = rand() % mpInfo->maxClips-1;
	if (mClip == 0) show = true;
	else show = false;
	mClipTimer.Start();
}

void Decor::Update(int delta_ticks)
{
	Shared::CheckClip(mClipTimer, mClip, mpInfo->interval + rand() % 50, mpInfo->maxClips, 0);
	if (mClip >= mpInfo->maxClips-1)
	{
		mX = rand() % WINDOW_WIDTH;
		mY = rand() % WINDOW_WIDTH;
		mClip = rand() % 2;
		if (mClip == 0) show = true;
		else show = false;
	}
	mY += 50 * (delta_ticks/1000.f);
}

void Decor::Draw(SDL_Surface *pdest)
{
	if (show)
		Shared::DrawSurface(mX, mY, mpInfo->pSurface, pdest, &mpInfo->pClips[mClip]);
}