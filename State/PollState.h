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
#ifndef POLLSTATE_H
#define POLLSTATE_H

#include "gamestate.h"
#include "Engine/Timer.h"
#include <sstream>

class FontInfo;
class NSprite;

class CPollState : public CGameState
{
public:
	void Init();
	void Cleanup();
	void Pause();
	void Resume();
	void KeyInput(const SDL_Event& rEvent);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pdest);

	static CPollState* Instance() {return &mIntroState;}
protected:
	CPollState() {}

	struct Tally
	{
		bool visible;
		int value;
		int count;
		int total;
		Point countPoint;
		Point totalPoint;
		std::stringstream countStr;
		std::stringstream totalStr;
	};

	bool TickCounter(Tally& rItem, int counterType, int countleft);
	void Reset(Tally& rItem);
private:
	static CPollState mIntroState;
	FontInfo* mpFont;
	SDL_Surface* mpBackground;
	int mAlpha;
	Timer mFadeTimer;
	Point banner_middle_pos;
	Point banner_left_pos;
	Point banner_right_pos;

	SDL_Surface* banner_middle;
	SDL_Surface* banner_side;
	float banner_speed;
	bool mExit; 
	bool mEnter; 
	bool mFadeout;
	bool mReady;
	bool mSkip;

	/* Totals */
	Tally mGem;
	Tally mCoin;
	Tally mQuartz;

	/* Sprites */
	NSprite* mpGem;
	NSprite* mpCoin;
	NSprite* mpQuartz;
	NSprite* mpReady;

	/*
	todo:
	1) Increment counter by 10/5/1
	2) Increase score by value
	3) Decrease interface count by counter
	*/
};

#endif