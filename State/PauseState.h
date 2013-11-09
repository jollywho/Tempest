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
#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "gamestate.h"
#include "Engine/Timer.h"

class Menu;
class Panel;

class CPauseState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void KeyInput(const SDL_Event& rEvent);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pdest);

	static CPauseState* Instance() {
		return &mPauseState;
	}

protected:
	CPauseState() { }

private:
	static CPauseState mPauseState;
    int mAlpha;
	Panel* mpPanel;
    Menu* mpMenu;
	Timer mFadeTimer;
	SDL_Surface* mpScreen;
	SDL_Rect mScreenBounds;
	bool mEnter; 
	bool mFadeout; 
	bool mSpan;

};

#endif