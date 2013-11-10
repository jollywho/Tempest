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
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Engine/Engine.h"

class CGameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void KeyInput(const SDL_Event& rEvent) = 0;
	virtual void Update(const int& rDeltaTime) = 0;
	virtual void Draw(SDL_Surface* dest) = 0;

	void ClearRequest()
	{ 
		mStateChange = false; 
		mStatePush = false;
		mStatePop = false;
	}
	void ChangeState(States::State id)
	{
		mRequestedState = id;
		mStateChange = true;
	}
	void PushState(States::State id)
	{
		mRequestedState = id;
		mStatePush = true;
	}
	void PopState()
	{ 
		mStatePop = true; 
	}

	bool IsStateChange() {return mStateChange;}
	bool IsStatePush() {return mStatePush;}
	bool IsStatePop() {return mStatePop;}

	States::State RequestedState() {return mRequestedState;}
protected:
   	CGameState() {}
private:
	States::State mRequestedState;
	bool mStateChange;
	bool mStatePush;
	bool mStatePop;
};

#endif