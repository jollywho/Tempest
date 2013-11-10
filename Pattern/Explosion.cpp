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
#include "Explosion.h"
#include "Game/Camera.h"
#include "State/Playstate.h"
#include "Engine/SpriteResource.h"
#include "Level/Level.h"

std::map<std::string, std::list<ExplosionInfo>> Explosion::msExplosions;

Explosion::Explosion(int x, int y, int xv, int yv, ExplosionInfo nfo)
{
	mDelete = false;
	mpInfo = &SpriteResource::RequestResource("Explosion", nfo.spriteId);
	mX = x-mpInfo->width / 2 + nfo.offsetX;
	mY = y-mpInfo->height / 2 + nfo.offsetY;
	mXVel = xv; mYVel = yv;
	mClip = 0;
	mDetTime = nfo.delay;

	if (nfo.magnitude > 4)
		Camera::Instance()->StartShake(nfo.magnitude);

	//if (nfo.residue)
	//	CPlayState::Instance()->mpLevel->objectList.push_back(new LayerObjbect(x, y));

	if (mDetTime != 0)  mStarted = false;
	else mStarted = true;

	mClipTimer.Start();
}

void Explosion::AddExplosionInfo(std::string expId, std::string spriteId,
	int magnitude, int delay, int offsetX, int offsetY, bool residue)
{
	std::list<ExplosionInfo> dataList;
	ExplosionInfo data;
	data.spriteId = spriteId; data.delay = delay; data.residue = residue;
	data.offsetX = offsetX; data.offsetY = offsetY; data.magnitude = magnitude;
	auto temp = msExplosions.find(expId);
	if (temp == msExplosions.end()) {
		dataList.push_back(data);
		msExplosions.insert(std::make_pair(expId,  dataList));
	}
	else
		temp->second.push_back(data);
}

void Explosion::RequestExplosion(std::string expId, int x, int y, int xv, int yv)
{
	printf("%s requested: \n", expId.c_str());
	auto temp = msExplosions.find(expId)->second;
	std::list<ExplosionInfo>::const_iterator it;
	for (auto it = temp.begin(); it != temp.end(); it++)
	{
		printf("Explosion %s\n", it->spriteId.c_str());
		CPlayState::Instance()->explosion_list.push_back(new Explosion(x,y,xv,yv,*it));
	}
}

void Explosion::ClearList()
{
	msExplosions.clear();
}

void Explosion::Update(Uint32 delta_ticks)
{
	if (!mStarted && mClipTimer.GetTicks() > mDetTime) {
		mStarted = true; mClipTimer.Start();}
	if (mStarted)
	{
		if (mClip >= mpInfo->maxClips-1)
			mDelete = true;
		Shared::CheckClip(mClipTimer, mClip, mpInfo->interval, mpInfo->maxClips, 0);
		mX += mXVel * (delta_ticks / 1000.f);
		mY += mYVel * (delta_ticks / 1000.f);
	}
}

void Explosion::Draw(SDL_Surface *pdest)
{
	if (mStarted)
		Camera::Instance()->DrawSurface(mX, mY, mpInfo->pSurface, pdest, &mpInfo->pClips[mClip]);
}