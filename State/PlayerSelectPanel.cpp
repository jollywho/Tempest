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
#include "PlayerSelectPanel.h"
#include "UI/NSprite.h"
#include "Game/GameScore.h"
#include "UI/Menu.h"
#include "Engine/SpriteResource.h"
#include "Weapon/MType.h"
#include "Engine/ResourceLoader.h"

PlayerSelectPanel::PlayerSelectPanel()
{
	printf("-PlayerSelectPanel Created-\n");
	mBack = false; mForward = false;
	ResourceLoader::ReadFile("Player");
	mpPlayer = new NSprite(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, &SpriteResource::RequestResource("Player", "angel_1"));
	mpTitle = Shared::LoadImage("Image/UI/select_player_title.png");
	mIndex = 1;
}

PlayerSelectPanel::~PlayerSelectPanel()
{
	printf("-PlayerSelectPanel Deleted-\n");
	delete mpPlayer;
	SDL_FreeSurface(mpTitle);
	for (auto it = mpBulletList.begin(); it != mpBulletList.end();)
	{
		delete (*it);
		it++; 
	}
	mpBulletList.clear();
}

void PlayerSelectPanel::KeyInput(const SDL_Event& rEvent)
{
	if (rEvent.key.keysym.sym == SDLK_ESCAPE || rEvent.key.keysym.sym == SDLK_x) mBack = true;
	if (1)
	//if (rEvent.key.keysym.sym == SDLK_z) //debug
	{
		mForward = true;
	}
	if (rEvent.key.keysym.sym == SDLK_DOWN) mIndex++;
	else if (rEvent.key.keysym.sym == SDLK_UP) mIndex--;
	if (mIndex > 3) mIndex = 1;
	if (mIndex < 1) mIndex = 3;

	if (rEvent.key.keysym.sym == SDLK_DOWN || rEvent.key.keysym.sym == SDLK_UP)
	{
		std::stringstream angel_name;
		angel_name << "angel_" << mIndex;
		delete mpPlayer;
		mpPlayer = new NSprite(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 
			&SpriteResource::RequestResource("Player", angel_name.str()));
	}
}

void PlayerSelectPanel::Update(const int& rDeltaTime)
{
	mpPlayer->Update();
	for (auto it = mpBulletList.begin(); it != mpBulletList.end();)
	{
		(*it)->Update(rDeltaTime);
		if ((*it)->RequestDelete())
		{
			delete (*it);
			it = mpBulletList.erase(it);	
		}
		else
		{
			it++;
		}
	}
}

void PlayerSelectPanel::Draw(SDL_Surface *pdest)
{
	mpPlayer->Draw(pdest);
}

void PlayerSelectPanel::DrawTop(SDL_Surface *pdest)
{
	if (!mForward)
		Shared::DrawSurface(0, 0, mpTitle, pdest);
}