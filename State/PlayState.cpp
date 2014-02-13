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
#include "playstate.h"
#include <sprig.h>
#include "Game/Camera.h"
#include "UI/Interface.h"
#include "Level/Level.h"
#include "Enemy/Enemy.h"
#include "UI/ScoreMSG.h"
#include "Item/Item.h"
#include "Weapon/PlayerBullet.h"
#include "Pattern/EnemyBullet.h"
#include "Pattern/Explosion.h"
#include "Engine/ResourceLoader.h"
#include "Engine/SpriteResource.h"

CPlayState CPlayState::mPlayState;

void CPlayState::Init()
{
	printf("CPlayState initialize\n");
	ClearRequest();
    mExit = false;
	mEnter = true;
	mReturn = false;
	mAlpha = 255;

	ResourceLoader::ReadFile("Item");
	ResourceLoader::ReadFile("Shop");
	ResourceLoader::ReadFile("Enemy");
	ResourceLoader::ReadFile("Attack");
	ResourceLoader::ReadFile("Explosion");
	ResourceLoader::ReadFile("Explosion", "explosion.dat");

	Enemy::Init();
	Item::Init();
	ScoreMSG::Init();
	
	mpPlayer = new Player();
	mpLevel = new Level();
	mpInterface = new Interface();

	mpPlayer->Spawn();
	mScanTimer.Start();
	mFadeTimer.Start();
}

CPlayState::~CPlayState()
{
    printf("delete playstate\n");
}

void CPlayState::Cleanup()
{
	printf("CPlayState Cleanup\n");
	Enemy::Cleanup();
	Item::Cleanup();
	ScoreMSG::Cleanup();
    ClearObjects();
	delete mpLevel;
	delete mpInterface;
	delete mpPlayer;
	SpriteResource::ClearResourceDir("Item");
	SpriteResource::ClearResourceDir("Shop");
	SpriteResource::ClearResourceDir("Enemy");
	SpriteResource::ClearResourceDir("Attack");
	SpriteResource::ClearResourceDir("Explosion");
	SpriteResource::ClearResourceDir("Player");
}

void CPlayState::ClearObjects()
{
    for (auto it = enemy_list.begin(); it != enemy_list.end(); it++)
        delete (*it);
    for (auto it = explosion_list.begin(); it != explosion_list.end(); it++)
        delete (*it);
	for (auto it = pl_bulletlist.begin(); it != pl_bulletlist.end(); it++)
		delete (*it);
	for (auto it = en_bulletlist.begin(); it != en_bulletlist.end(); it++)
		delete (*it);
    for (auto it = item_list.begin(); it != item_list.end(); it++)
        delete (*it);
    enemy_list.clear();
	explosion_list.clear();
	pl_bulletlist.clear();
	en_bulletlist.clear();
    item_list.clear();
}

template <class T>
void CPlayState::UpdateList(std::list<T>& rList, const int& rDeltaTime)
{
	for (auto it = rList.begin(); it != rList.end();)
	{
		if ((*it)->RequestDelete())
		{
			delete (*it);
			it = rList.erase(it);	
		}
		else
		{
			(*it)->Update(rDeltaTime);
			++it;
		}
	}
}

template <class T>
void CPlayState::DrawList(std::list<T>& rList, SDL_Surface* pdest)
{
	for (auto it = rList.begin(); it != rList.end(); ++it)
	{
		(*it)->Draw(pdest);
	}
}

void CPlayState::Pause()
{
	printf("CPlayState Pause\n");
	//todo: release/ set default keys
}

void CPlayState::Resume()
{
	printf("CPlayState Resume\n");
	if (mExit)
	{
		mExit = false;
		mAlpha = 255;
		mReturn = true;
	}
}

void CPlayState::NewLevel()
{

}

void CPlayState::KeyInput(const SDL_Event& rEvent)
{
	mpPlayer->KeyInput(rEvent);
	if (rEvent.type == SDL_KEYDOWN)
	{
		if (rEvent.key.keysym.sym == SDLK_RETURN && rEvent.key.keysym.sym == SDLK_LSHIFT)
			PushState(State::CONTINUE);
		if (rEvent.key.keysym.sym == SDLK_RETURN && rEvent.key.keysym.sym != SDLK_LSHIFT)
			mExit = true;
		if (rEvent.key.keysym.sym == SDLK_ESCAPE)
			PushState(State::PAUSE);
		if (rEvent.key.keysym.sym == SDLK_BACKQUOTE)
			PushState(State::SHOP);
	}
}

void CPlayState::Update(const int& rDeltaTime)
{
	if (mEnter || mReturn)
	{
		if (mAlpha > 0) 
		{
			if (mFadeTimer.GetTicks() > 10) 
			{
				mAlpha -= 5;
				mFadeTimer.Start(); 
			} 
		}
		else
		{
			mEnter = false;
			mReturn = false;
		}
	}
	if (mExit)
	{
		if (mAlpha < 255) 
		{
			if (mFadeTimer.GetTicks() > 30) 
			{
				mAlpha += 5;
				mFadeTimer.Start(); 
			} 
		}
		else
			PushState(State::POLL);
	}
	Camera::Instance()->Update(mpPlayer->GetOuterBounds().rect.x, rDeltaTime);
	mpLevel->Update(rDeltaTime);
	mpLevel->LoadEnemies(enemy_list);
	mpPlayer->Update(rDeltaTime);

	if (mScanTimer.GetTicks() > 30)
	{
		for (auto it = pl_bulletlist.begin(); it != pl_bulletlist.end(); it++)
		{
			(*it)->DetectCollision();
		}
		mScanTimer.Start();
	}
	UpdateList(pl_bulletlist, rDeltaTime);
	UpdateList(en_bulletlist, rDeltaTime);
	UpdateList(enemy_list, rDeltaTime);
	UpdateList(item_list, rDeltaTime);
	UpdateList(score_list, rDeltaTime);
	UpdateList(explosion_list, rDeltaTime);

	mpInterface->Update(rDeltaTime);
}

void CPlayState::Draw(SDL_Surface* pdest)
{
	mpLevel->Draw(pdest);

	DrawList(enemy_list, pdest);
	DrawList(pl_bulletlist, pdest);
	
	if (mExit || mReturn)
		SPG_RectFilledBlend(pdest,GAME_BANNER_WIDTH, 0,GAME_BOUNDS_WIDTH,WINDOW_HEIGHT, 16777215, mAlpha);
	if (mEnter)
		SPG_RectFilledBlend(pdest,GAME_BANNER_WIDTH, 0,GAME_BOUNDS_WIDTH,WINDOW_HEIGHT, 0, mAlpha);

	mpPlayer->Draw(pdest);
	DrawList(explosion_list, pdest);
	DrawList(en_bulletlist, pdest);
	DrawList(item_list, pdest);
	DrawList(score_list, pdest);

	mpInterface->Draw(pdest);
}