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
#include "NSprite.h"
#include "Engine/SpriteResource.h"

NSprite::NSprite(float x, float y, SpriteInfo* pInfo, bool doesStop, bool isReverse)
	: mBounds(x, y, pInfo->width, pInfo->height)
{
	mBounds.rect.x = x - pInfo->width/2; 
	mBounds.rect.y = y - pInfo->height/2;

	mpInfo = pInfo;
	mDir = -1;
	mClip = 0; 

	mStop = doesStop;
	mReverse = isReverse;
	mDone = false;
	mClip = rand() % (pInfo->maxClips-1);

	mClipTimer.Start();
}

NSprite::~NSprite() 
{
}

void NSprite::Reset()
{
	mClip = 0;
	mDone = false;
	mClipTimer.Start();
}

void NSprite::SetPos(Point& rCenter)
{
	mBounds.rect.x = rCenter.x - mpInfo->width/2; 
	mBounds.rect.y = rCenter.y - mpInfo->height/2;
}

void NSprite::Update()
{
	if (mDone) return;
	if (mReverse)
	{
		if (mClipTimer.GetTicks() > mpInfo->interval)
		{ 
			if (mClip > 0 && mClip < mpInfo->maxClips-1)
				mClip+=mDir;
			else {
				mDir = mDir * -1; mClip+=mDir; }
			mClipTimer.Start();
		}
	}
	else if (mStop && !mDone)
	{
		Shared::CheckClip(mClipTimer, mClip, mpInfo->interval, mpInfo->maxClips, mpInfo->maxClips);
		mDone = mClip >= mpInfo->maxClips? true: false;
	}
	else
		Shared::CheckClip(mClipTimer, mClip, mpInfo->interval, mpInfo->maxClips, 0);
}

void NSprite::Draw(SDL_Surface *pdest)
{
	if (mDone) return;
	Shared::DrawSurface(mBounds.rect.x, mBounds.rect.y, mpInfo->pSurface, pdest, &mpInfo->pClips[mClip]);
}