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
#ifndef ENGINE_H
#define ENGINE_H
 
#include "Engine/Shared.h"
#include <vector>

class CGameState;

namespace States
{
	enum State
	{
		INTRO,
		PLAY,
		POLL,
		NAME,
		PAUSE,
		CONTINUE,
		GAMEOVER,
		SHOP,
	};
}
typedef States::State State;

class CEngine 
{
private:
	int mWidth;
	int mHeight;
	bool mQuit;
	const char* mpTitle;
	SDL_Surface* mpScreen;
	bool mMinimized;
	Uint32 mPrevTime;
	Timer mDelta;
protected:
	void DoInput();
	void DoThink();
	void DoRender();
	void DoRequest();
 
	void DoStateChange(States::State id);
	void DoStatePush(States::State id);
	void DoStatePop();
	void SetSize(const int& rWidth, const int& rHeight);

	std::vector<CGameState*> mpStates;
	SDL_Event mEvent;
public:
	CEngine();
	virtual ~CEngine();
 
	void Init();
	void Start();
 
	virtual void AdditionalInit() {}
	virtual void Think(const int& rDeltaTime) {}
	virtual void Render(SDL_Surface* pdest) {}
	virtual void End() {}
	virtual void WindowActive() {}
	virtual void WindowInactive() {}
	void SetTitle(const char* pTitle);
	const char* GetTitle();
 
	SDL_Surface* GetSurface();
	CGameState*	StateInstance(State id);
	int GetFPS();
};
 
#endif // ENGINE_H