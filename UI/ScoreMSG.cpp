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
#include "ScoreMSG.h"
#include "Game/Camera.h"
#include "State/playstate.h"
#include "UI/Interface.h"
#include "Player/Player.h"
#include "Game/Gamescore.h"
#include "Engine/SFX.h"

SDL_Surface* ScoreMSG::mspSurfaceFade[4];
NFont ScoreMSG::msFontFade[4];
Timer ScoreMSG::msTallyTimer;
int ScoreMSG::msTallyTotal = 0;
int ScoreMSG::msExtend = 0;

ScoreMSG::ScoreMSG(int x, int y, int xDir, int value)
{
	mClip = 0;

	if (msTallyTimer.GetTicks() < 50 && msExtend < 2000)
	{
		mDelete = true;
		msTallyTotal += value;
		msExtend += 50;
		GameScore::Instance()->IncreaseScore(value);
	}
	else
	{
		msExtend = 0;
		msTallyTotal = value;
		mDelete = false;
		mValue = value;
		mMsg << "+" << mValue;
		GameScore::Instance()->IncreaseScore(value);
		mX = x + (rand() % 20)-40; 
		mY = y - (rand() % 20)+40;

		xvel = (xDir * 50);
		yvel = -50;
		mDurationTimer.Start();
		mClipTimer.Start();
	}
	msTallyTimer.Start();
}

ScoreMSG::~ScoreMSG()
{
}

void ScoreMSG::Init()
{
	for (int i = 0; i<4; i++)
	{
		std::stringstream ss;
		ss << "Font/GoldNoonFade"<< i << ".png";
		mspSurfaceFade[i] = Shared::LoadImage(ss.str());
		msFontFade[i].load(SDL_GetVideoSurface(), mspSurfaceFade[i]);
	}
	msTallyTimer.Start();
}

void ScoreMSG::Cleanup()
{
	for (int i = 0; i<4; i++)
		SDL_FreeSurface(mspSurfaceFade[i]);
}

void ScoreMSG::Update(Uint32 delta_ticks)
{
	Shared::CheckClip(mClipTimer, mClip, 300 + msExtend, 3, 3);
	mX += xvel * (delta_ticks/1000.f);
	mY += yvel * (delta_ticks/1000.f);
	if (mDurationTimer.GetTicks() > 800 + msExtend) { mDelete = true;}
	if (mValue < msTallyTotal)
	{
		mValue++;
		SFX::PlaySoundResource("tick");
	}
	mMsg.str("");
	mMsg << "+" << mValue;
}

void ScoreMSG::Draw(SDL_Surface *pdest)
{
	msFontFade[mClip].draw(mX-Camera::Instance()->CameraX(), mY, mMsg.str().c_str());
}