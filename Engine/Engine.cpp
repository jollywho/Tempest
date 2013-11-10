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
#include "Engine.h"
#include "SDL_ttf.h"
#include "Engine/SFX.h"
#include <windows.h> // For the WaitMessage() function.
#include "State/GameState.h"
#include "State/IntroState.h"
#include "State/PlayState.h"
#include "State/PollState.h"
#include "State/PauseState.h"
#include "State/ContinueState.h"
#include "State/ShopState.h"

CEngine::CEngine()
{
	mWidth = WINDOW_WIDTH;
	mHeight	= WINDOW_HEIGHT;
	mpTitle	= 0;
	mpScreen = 0;
	mMinimized = false;
}

CEngine::~CEngine()
{
	SDL_Quit();
}

void CEngine::SetSize(const int& rWidth, const int& rHeight)
{
	SDL_WM_SetIcon(IMG_Load("icon.png"), NULL);

	mWidth = rWidth;
	mHeight = rHeight;
	mpScreen = SDL_SetVideoMode(rWidth, rHeight, 0, SDL_SWSURFACE| SDL_DOUBLEBUF);
}

void CEngine::Init()
{
	atexit(SDL_Quit);
 
	SDL_putenv("SDL_VIDEO_CENTERED=center");
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
 
	SetSize(mWidth, mHeight);
 
	if (mpScreen == NULL) 
	{
		fprintf(stderr, "Unable to set up video: %s\n", SDL_GetError());
		exit(1);
	}
	if (TTF_Init() < 0)
	{
		fprintf(stderr, "Unable to initialize TTF: %s\n", SDL_GetError());
		exit(1);
	}

	SFX::Init();
	AdditionalInit();
}

CGameState* CEngine::StateInstance(State id)
{
	switch(id)
	{
		case State::INTRO:
			return CIntroState::Instance();
			break;
		case State::PLAY:
			return CPlayState::Instance();
			break;
		case State::POLL:
			return CPollState::Instance();
			break;
		case State::PAUSE:
			return CPauseState::Instance();
			break;
		case State::SHOP:
			return CShopState::Instance();
			break;
		case State::CONTINUE:
			return CContinueState::Instance();
			break;
		default:
			return CIntroState::Instance();
			break;
	}
}

void CEngine::DoStateChange(States::State id) 
{
	for (auto it = mpStates.begin(); it != mpStates.end();) {

		(*it)->Cleanup();
		it = mpStates.erase(it);
	}

	mpStates.push_back(StateInstance(id));
	mpStates.back()->Init();
}

void CEngine::DoStatePush(States::State id)
{
	mpStates.push_back(StateInstance(id));
    mpStates.back()->Init();
}

void CEngine::DoStatePop()
{
    if (!mpStates.empty()) {
        mpStates.back()->Cleanup();
        mpStates.pop_back();
    }

    if (!mpStates.empty()) {
        mpStates.back()->Resume();
    }
}

void CEngine::DoRequest()
{
	if (mpStates.back()->IsStateChange())
		DoStateChange(mpStates.back()->RequestedState());

	if (mpStates.back()->IsStatePush())
	{
		DoStatePush(mpStates.back()->RequestedState());
	}
	if (mpStates.back()->IsStatePop())
	{
		DoStatePop();
	}

	mpStates.back()->ClearRequest();
}

void CEngine::Start()
{
	mQuit = false;
 
	mPrevTime = 0;
	mPrevTime = SDL_GetTicks();
	
	while (!mQuit)
	{
		DoInput();
		
		if (mMinimized) 
		{
			WaitMessage();
		}
		else 
		{
			DoThink();
			DoRequest();
			DoRender();

			Uint32 curr_time = SDL_GetTicks();
			Uint32 elapsed_time = curr_time - mPrevTime;
			//if(elapsed_time < 15)
			//{
				//SDL_Delay(15 - elapsed_time);
				curr_time = SDL_GetTicks();
				elapsed_time = curr_time - mPrevTime;
			//}
			mPrevTime = curr_time;
		}
	}
	End();
}

void CEngine::DoInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{	
		switch (event.type) 
		{
		case SDL_QUIT:
			mQuit = true;
			break;
 
		case SDL_ACTIVEEVENT:
			if (event.active.state & SDL_APPACTIVE) {
				if (event.active.gain) {
					mMinimized = false;
					WindowActive();
				} else {
					mMinimized = true;
					WindowInactive();
				}
			}
			break;
		}
	mpStates.back()->KeyInput(event);
	}
}

void CEngine::DoThink() 
{
	Think(mDelta.GetTicks());
	mDelta.Start();
}
 
void CEngine::DoRender()
{
	Render(GetSurface());
	SDL_Flip(mpScreen);
}

void CEngine::SetTitle(const char* pTitle)
{
	mpTitle = pTitle;
	SDL_WM_SetCaption(pTitle, 0);
}

const char* CEngine::GetTitle()
{
	return mpTitle;
}
 
SDL_Surface* CEngine::GetSurface()
{ 
	return mpScreen;
}