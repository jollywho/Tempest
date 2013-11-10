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
#include "Engine/Shared.h"
#include "Layer.h"
#include "Level.h"
#include "Game/Camera.h"
#include "State/playstate.h"
#include "Game/GameScore.h"
#include "Enemy/Enemy.h"
#include "Factory.h"

Level::Level()
{
    printf("Level01 initialize\n");

	mpBackground = Shared::LoadImage("Image/Levels/level02.png");
	mpTopSurface = Shared::LoadImage("Image/Levels/raindrops.png");
	mpTop = new Layer(mpTopSurface, 720, 0);
	mpTop->Start();

	mLevelEnd = 6400;
	Camera::Instance()->Reset();
	GameScore::Instance()->ResetLevel();
	
	Factory::ReadFile("Script/level_01.dat", enemy_cache);
	mReader = enemy_cache.begin();
}

void Level::LoadEnemies(std::list<Enemy*>& rList)
{
	if (!enemy_cache.empty())
	{
		if ((*mReader)->CheckBounds())
		{
			rList.push_back((*mReader));
			mReader = enemy_cache.erase(mReader);
		}
	}
}

Level::~Level()
{
	printf("Level01 Cleanup\n");
	SDL_FreeSurface(mpBackground);
	SDL_FreeSurface(mpTopSurface);
	for (auto it = enemy_cache.begin(); it != enemy_cache.end();) {
        delete (*it);
        it++;}
	enemy_cache.clear();
}

void Level::Update(const int& rDeltaTime)
{
	mpTop->Update(rDeltaTime, Camera::Instance()->CameraSpeed() * 3);
	mBounds.x = Camera::Instance()->CameraX();
	mBounds.y = Camera::Instance()->CameraY2() - WINDOW_HEIGHT;
}

void Level::Draw(SDL_Surface *pdest)
{
	Shared::DrawSurface(GAME_BANNER_WIDTH, 0, mpBackground, pdest, &mBounds);

	mpTop->Draw(pdest);
}