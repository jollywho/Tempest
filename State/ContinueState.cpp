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
#include "continuestate.h"
#include "UI/NSprite.h"
#include "Engine/FontResource.h"
#include "Engine/SpriteResource.h"
#include <sprig.h>
#include "UI/Menu.h"

CContinueState CContinueState::mContState;

void CContinueState::Init()
{
	printf("CContinueState Init\n");

	ClearRequest();
	mpScreen = SDL_DisplayFormatAlpha(SPG_CopySurface(SDL_GetVideoSurface()));
	mScreenBounds.x = GAME_BANNER_WIDTH;
	mScreenBounds.y = 0;
	mScreenBounds.w = GAMESCREEN_WIDTH;
	mScreenBounds.h = GAMESCREEN_HEIGHT;
	
	mpTitle = new NSprite(WINDOW_WIDTH/2, 195, &SpriteResource::RequestResource("UI", "cont_title"), false, true);
	mpCounter = new NSprite(WINDOW_WIDTH/2, 195 + 48, &SpriteResource::RequestResource("UI", "cont_counter"), true);
	mpContTitle = Shared::LoadImage("Image/UI/cont_title_frame.png");
	mpContCount = Shared::LoadImage("Image/UI/cont_count_frame.png");

	mAlpha = 0;

	/* Menu */
    mpMenu = new Menu();
    mpMenu->AddItem(WINDOW_WIDTH/2, 320, "Yes");
    mpMenu->AddItem(WINDOW_WIDTH/2, 380, "No");

	mEnter = true; 
	mFadeout = false; 
	mSpan = false;

	mCountdownTimer.Start();
	mFadeTimer.Start();
}

void CContinueState::Cleanup()
{
	printf("CContinueState Cleanup\n");
	SDL_FreeSurface(mpContTitle);
	SDL_FreeSurface(mpContCount);
	SDL_FreeSurface(mpScreen);
	delete mpMenu;
	delete mpTitle;
	delete mpCounter;
}

void CContinueState::KeyInput(const SDL_Event& rEvent)
{
	if (rEvent.key.keysym.sym == SDLK_z)
	{
		mpMenu->Select();
		if (mpMenu->GetIndex() == 1) { PopState(); }
		if (mpMenu->GetIndex() == 2) { ChangeState(State::INTRO); } //todo: gameoverstate
	}
	if (rEvent.key.keysym.sym == SDLK_DOWN) mpMenu->MoveIndex(1);
	else if (rEvent.key.keysym.sym == SDLK_UP) mpMenu->MoveIndex(-1);
}

void CContinueState::Update(const int& rDeltaTime)
{
	mpMenu->Update(rDeltaTime, mAlpha);
	mpTitle->Update();
	mpCounter->Update();
	if (mpCounter->IsDone())
		PopState();
	if (mFadeTimer.GetTicks() > 10)
	{
		if (mAlpha < 100) mAlpha+=5;
		mFadeTimer.Start();
	}
}

void CContinueState::Draw(SDL_Surface* pdest)
{
	Shared::DrawSurface(GAME_BANNER_WIDTH, 0, mpScreen, pdest, &mScreenBounds);
	SPG_RectFilledBlend(pdest, GAME_BANNER_WIDTH, 0, GAME_BOUNDS_WIDTH, GAME_BOUNDS_HEIGHT, 0, mAlpha);
	mpMenu->Draw(pdest);
	Shared::DrawSurface(WINDOW_WIDTH/2 - 225, 150, mpContTitle, pdest);
	Shared::DrawSurface(WINDOW_WIDTH/2 - 98, 200, mpContCount, pdest);
	mpTitle->Draw(pdest);
	mpCounter->Draw(pdest);
}