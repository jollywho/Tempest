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
#include "ModeSelectPanel.h"
#include "UI/NSprite.h"
#include "Game/GameScore.h"
#include "UI/Menu.h"
#include "Engine/SpriteResource.h"
#include "playerselectpanel.h"

/*
ModeModeSelectPanel --> WeaponModeSelectPanel

Mode:
Banner Title - leftright enter/exit from offscreen
Menu - of surfaces. animate when selectedindex. stop when leaving
Menu Frame - topdown enter from under intro panels

Weapon:
Banner Title - leftright enter/exit from offscreen
Demo - downup enter from under intro panels
Some type of selector using icons

*/
Point HIDE_POINT = Point(-500, -500);
Point START_POINT = Point(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

ModeSelectPanel::ModeSelectPanel()
{
	printf("-ModeSelectPanel Created-\n");
	mBack = false; mForward = false;

	mpTitle = Shared::LoadImage("Image/UI/select_mode_title.png");

	//default mode sprite offscreen
	mpMode = new NSprite(HIDE_POINT.x, HIDE_POINT.y, &SpriteResource::RequestResource("UI", "mode_normal"), false, true);
	mpPanel = NULL;
	mpMenu = new Menu();
	//
    mpMenu->AddItem(WINDOW_WIDTH/2, 200, "Normal");
	mpMenu->AddItem(WINDOW_WIDTH/2, 260, "Ultra");
    mpMenu->AddItem(WINDOW_WIDTH/2, 320, "Insane");
}

ModeSelectPanel::~ModeSelectPanel()
{
	printf("-ModeSelectPanel Deleted-\n");
	if (mpPanel != NULL) {
		delete mpPanel;
		mpPanel = NULL;
	}
	SDL_FreeSurface(mpTitle);
	delete mpMode;
	delete mpMenu;

}

void ModeSelectPanel::KeyInput(const SDL_Event& rEvent)
{
	if (mpPanel != NULL) 
	{
		mpPanel->KeyInput(rEvent);
	}
	else
	{
		if (rEvent.key.keysym.sym == SDLK_ESCAPE || rEvent.key.keysym.sym == SDLK_x) mBack = true;
		if (1)
		//if (rEvent.key.keysym.sym == SDLK_z) debug
		{
			mMode = START_POINT;
			delete mpMode;
			mpMode = new NSprite(mMode.x, mMode.y, 
					&SpriteResource::RequestResource("UI", GameScore::GetModeEquivalent(mpMenu->GetIndex(), true)), false, true);

			GameScore::Instance()->SetMode(mpMenu->GetIndex());
			mpPanel = new PlayerSelectPanel(); mpMenu->Reset();
		}
		if (rEvent.key.keysym.sym == SDLK_DOWN) mpMenu->MoveIndex(1);
		else if (rEvent.key.keysym.sym == SDLK_UP) mpMenu->MoveIndex(-1);
	}
}

void ModeSelectPanel::Update(const int& rDeltaTime)
{
	if (mpPanel != NULL)
	{
		mForward = mpPanel->Forward();
		if (mpPanel->Back())
		{
			mMode = HIDE_POINT;
			mpMode->SetPos(mMode);	//rehide
			mpMenu->Reset();
			delete mpPanel;
			mpPanel = NULL;
		}
		else
			mpPanel->Update(rDeltaTime);

		if (mMode.y > GAME_UI_MODE_Y) mMode.y -= 300 * rDeltaTime/1000.f;
		else mMode.y = GAME_UI_MODE_Y;
			
		mpMode->SetPos(mMode);
	}
	mpMode->Update();
	mpMenu->Update(rDeltaTime, 255);
}

void ModeSelectPanel::Draw(SDL_Surface *pdest)
{
	if (mpPanel != NULL)
		mpPanel->Draw(pdest);
	else
	{
		mpMenu->Draw(pdest);
	}
}

void ModeSelectPanel::DrawTop(SDL_Surface *pdest)
{
	if (mpPanel == NULL && !mForward)
		Shared::DrawSurface(0, 0, mpTitle, pdest);
	else
		mpPanel->DrawTop(pdest);
	mpMode->Draw(pdest);
}