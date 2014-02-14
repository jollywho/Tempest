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
#include "HealthBar.h"
#include "Engine/SpriteResource.h"
#include "NSprite.h"

HealthBar::HealthBar(std::string id_t, std::string id_s, Point& p, bool draw_border, bool left_dir)
{
	mBorder = draw_border;
	mpBorder = &SpriteResource::RequestTextureResource("UI", id_t);
	mpInfo = &SpriteResource::RequestResource("UI", id_s);
	mpMarker = new NSprite(0, 0, &SpriteResource::RequestResource("UI", "marker"));
	MAX_VALUE = 10;
	mVal = MAX_VALUE;
	mLeftDir = left_dir;
	//mpExplosion = new NSprite(0, 0, &SpriteResource::RequestResource("UI", "ui_explosion"), false, false);
	mClip = 1; 
	mRecRate = 1; 
	mDir = 1;
	mPos.x = p.x;
	if (draw_border) mPos.x = p.x - mpBorder->width;
	if (mPos.x < 0) mPos.x = 0;
	mPos.y = p.y - mpBorder->height;
	mClipTimer.Start();
	mRecTimer.Start();
}
HealthBar::~HealthBar() 
{

}

void HealthBar::SetMaxVal(int& val)
{
	mVal = ((float)mVal / (float)MAX_VALUE) * val;
	MAX_VALUE  = val;
}

void HealthBar::Update()
{
	if (mClipTimer.GetTicks() > mpInfo->interval)
	{ 
		if (mClip > 0 && mClip < mpInfo->maxClips-1)
			mClip += mDir;
		else {
			mDir *= -1; mClip += mDir;}
		mClipTimer.Start();
	}

	if (mRecTimer.GetTicks() > 30)
	{
		mVal += mRecRate;
		mVal > MAX_VALUE ? mVal = MAX_VALUE : 0;
		mRecTimer.Start();
	}

	//todo: have nsprite on edge

	for (int i = 0; i < mpInfo->maxClips; i++)
	{
		if (mLeftDir)
			mpInfo->pClips[i].w = ((float)mVal / (float)MAX_VALUE) * mpInfo->width;
		else
			mpInfo->pClips[i].x = mpInfo->width - ((float)mVal / (float)MAX_VALUE) * mpInfo->width;
	}

	mpMarker->SetPos(Point(mPos.x, mPos.y));
	mpMarker->Update();
}

void HealthBar::Draw(SDL_Surface *pdest) 
{
	Shared::DrawSurface(mPos.x, mPos.y, mpInfo->pSurface, pdest, &mpInfo->pClips[mClip]);

	if (mBorder)
		Shared::DrawSurface(mPos.x, mPos.y, mpBorder->pSurface, pdest);
	
	//mpMarker->Draw(mpBorder->pSurface);
}