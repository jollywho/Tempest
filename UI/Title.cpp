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
#include "Title.h"
#include <sstream>

Title::Title(const char* title)
{
	mStart = true; mDone = false;
	for (int i=0; i<4; i++)
	{
		std::ostringstream ss;
		ss << "Font/GoldNoonFadeRev"<< i << ".png";
		mspSurfaceFade[i] = Shared::LoadImage(ss.str());
		mpFont[i].load(SDL_GetVideoSurface(), mspSurfaceFade[i]);
	}
	mLength = 0;
	mMaxLength = 0;
	for (int i=0; title[i] != '\0'; i++)
	{
		mChars[i].fade = 0;
		mChars[i].ch[0] = title[i];
		mChars[i].ch[1] = '\n';
		mMaxLength++;
	}
	mPos = Point(WINDOW_WIDTH - 50, GAME_UI_TOP);
	mTimer.Start();
}

Title::~Title()
{
	for (int i=0; i<3; i++)
		SDL_FreeSurface(mspSurfaceFade[i]);
}


void Title::Update(const int& rDeltaTime)
{
	if (mDone) return;
	if (mLength < mMaxLength) 
	{
		if (mTimer.GetTicks() > 90)
		{
			mLength++;
			for (int i=0; i < mLength+1; i++)
			{
				if (mChars[i].fade < 3)
				{
					mChars[i].fade++;
				}
			}
			if (mChars[mLength].ch[0] == '\n')
				mTimer.SetTicks(120);
			else
				mTimer.Start();
		}
	}
	else {
		if (!mFinTimer.IsStarted()) mFinTimer.Start();
		if (mFinTimer.GetTicks() > 800) mDone = true;
	}
}

void Title::Draw(SDL_Surface *pdest)
{
	if (mDone) return;
	for (int i=0; i < mLength; i++)
	{
		mpFont[mChars[i].fade].draw(mPos.x, mPos.y + (20 * i), mChars[i].ch);
	}
}