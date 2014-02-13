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
#include "pausestate.h"
#include <sprig.h>
#include "UI/Menu.h"
#include "optionpanel.h"

CPauseState CPauseState::mPauseState;

void CPauseState::Init()
{
	printf("CPauseState Init\n");

	ClearRequest();
	mpScreen = SDL_DisplayFormatAlpha(SDL_GetVideoSurface());

	mScreenBounds.x = GAME_BANNER_WIDTH;
	mScreenBounds.y = 0;
	mScreenBounds.w = GAMESCREEN_WIDTH;
	mScreenBounds.h = GAMESCREEN_HEIGHT;
	mpPanel = NULL;
	mAlpha = 0;

    mpMenu = new Menu();
    mpMenu->AddItem(WINDOW_WIDTH / 2, 200, "Return");
    mpMenu->AddItem(WINDOW_WIDTH / 2, 260, "Options");
	mpMenu->AddItem(WINDOW_WIDTH / 2, 320, "Quit to Menu");
    mpMenu->AddItem(WINDOW_WIDTH / 2, 380, "Exit Game");

	mEnter = true; 
	mFadeout = false; 
	mSpan = false;

	mFadeTimer.Start();
}

void CPauseState::Cleanup()
{
	printf("CPauseState Cleanup\n");
	if (mpPanel != NULL)
	{
		delete mpPanel;
		mpPanel = NULL;
	}
	SDL_FreeSurface(mpScreen);
	delete mpMenu;
}

void CPauseState::Pause()
{
	printf("CPauseState Pause\n");
}

void CPauseState::Resume()
{
	printf("CPauseState Resume\n");
}

void CPauseState::KeyInput(const SDL_Event& rEvent)
{
	if (mpPanel != NULL) 
	{
		mpPanel->KeyInput(rEvent);
	}
	else
	{
		if (rEvent.type == SDL_KEYDOWN)
		{
			if (rEvent.key.keysym.sym == SDLK_ESCAPE) 
				PopState();
			if (rEvent.key.keysym.sym == SDLK_z)
			{
				mpMenu->Select();
				if (mpMenu->GetIndex() == 1) { PopState();}
				if (mpMenu->GetIndex() == 2) { mpPanel = new OptionPanel(); mpMenu->Reset();}
				if (mpMenu->GetIndex() == 3) { ChangeState(State::INTRO);}
				if (mpMenu->GetIndex() == 4) { SDL_Event event_quit; event_quit.type = SDL_QUIT;  SDL_PushEvent(&event_quit);}
			}
			if (rEvent.key.keysym.sym == SDLK_DOWN)
				mpMenu->MoveIndex(1);
			else if (rEvent.key.keysym.sym == SDLK_UP)
				mpMenu->MoveIndex(-1);
		}
	}
}

void CPauseState::Update(const int& rDeltaTime)
{
	if (mpPanel != NULL)
	{
		if (mpPanel->Back())
		{
			mpMenu->Reset();
			delete mpPanel;
			mpPanel = NULL;
		}
		else
			mpPanel->Update(rDeltaTime);
	}

	mpMenu->Update(rDeltaTime, mAlpha);
	if (mFadeTimer.GetTicks() > 10)
	{
		if (mAlpha < 100) mAlpha += 5;
		mFadeTimer.Start();
	}
}

void CPauseState::Draw(SDL_Surface* pdest)
{
	Shared::DrawSurface(GAME_BANNER_WIDTH, 0, mpScreen, pdest, NULL);
	SPG_RectFilledBlend(pdest, GAME_BANNER_WIDTH, 0, GAME_BOUNDS_WIDTH, GAME_BOUNDS_HEIGHT, 0, mAlpha);

	if (mpPanel != NULL)
		mpPanel->Draw(pdest);
	else
		mpMenu->Draw(pdest);
}
