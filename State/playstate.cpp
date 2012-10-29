#include "playstate.h"
#include <sprig.h>
#include "Game/Camera.h"
#include "Game/Interface.h"
#include "Level/Level01.h"
#include "Enemy/Enemy.h"
#include "UI/ScoreMSG.h"
#include "Item/Item.h"
#include "Weapon/PlayerBullet.h"
#include "Pattern/EnemyBullet.h"
#include "ENemy/Zown.h"

CPlayState CPlayState::mPlayState;

void CPlayState::Init()
{
	printf("CPlayState initialize\n");
	ClearRequest();
    mExit = false;
	mEnter = true;
	mAlpha = 255;

	Enemy::Init();
	EnemyBullet::Init();
	Item::Init();
	ScoreMSG::Init();
	
	mpPlayer = new Player();
	mpLevel = new Level01();
	mpInterface = new Interface();

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
    ClearObjects();
	delete mpLevel;
	delete mpInterface;
	delete mpPlayer;
}

void CPlayState::ClearObjects()
{
    for (auto it = enemy_list.begin(); it != enemy_list.end();) {
        delete (*it);
        it++; }
	for (auto it = pl_bulletlist.begin(); it != pl_bulletlist.end();) {
		delete (*it);
		it++; }
	for (auto it = en_bulletlist.begin(); it != en_bulletlist.end();) {
		delete (*it);
		it++; }
    for (auto it = item_list.begin(); it != item_list.end();) {
        delete (*it);
        it++; }
    enemy_list.clear();
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
			it++;
		}
	}
}

template <class T>
void CPlayState::DrawList(std::list<T>& rList, SDL_Surface* pDest)
{
	for (auto it = rList.begin(); it != rList.end(); it++)
	{
		(*it)->Draw(pDest);
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
		mEnter = true;
	}
}

void CPlayState::Back()
{
	printf("CPlayState Return\n");

}

void CPlayState::NewLevel()
{

}

void CPlayState::KeyInput(const KeyStruct& rKeys)
{
	mpPlayer->KeyInput(rKeys);
	//if (rKeys.enter) mExit = true;
	if (rKeys.enter) PushState(State::Continue);
	if (rKeys.esc) PushState(State::Pause);
}

void CPlayState::Update(const int& rDeltaTime)
{
	if (mEnter)
	{
		if (mAlpha > 0) 
		{
			if (mFadeTimer.GetTicks() > 10) 
			{
				mAlpha-=5;
				mFadeTimer.Start(); 
			} 
		}
		else
			mEnter = false;
	}
	if (mExit)
	{
		if (mAlpha < 255) 
		{
			if (mFadeTimer.GetTicks() > 10) 
			{
				mAlpha+=5;
				mFadeTimer.Start(); 
			} 
		}
		else
			PushState(State::Poll);
	}
	Camera::Update(mpPlayer->GetOuterBounds().rect.x, rDeltaTime);
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

	mpInterface->Update(rDeltaTime);
}

void CPlayState::Draw(SDL_Surface* pDest)
{
	mpLevel->Draw(pDest);

	DrawList(enemy_list, pDest);
	DrawList(pl_bulletlist, pDest);
	
	if (mExit)
		SPG_RectFilledBlend(pDest,GAME_BANNER_WIDTH,0,GAME_BOUNDS_WIDTH,WINDOW_HEIGHT, 16777215, mAlpha);
	if (mEnter)
		SPG_RectFilledBlend(pDest,GAME_BANNER_WIDTH,0,GAME_BOUNDS_WIDTH,WINDOW_HEIGHT, 0, mAlpha);

	mpPlayer->Draw(pDest);

	DrawList(en_bulletlist, pDest);
	DrawList(item_list, pDest);
	DrawList(score_list, pDest);

	mpInterface->Draw(pDest);
	
}