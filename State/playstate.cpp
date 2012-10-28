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

CPlayState CPlayState::m_PlayState;

void CPlayState::Init()
{
	printf("CPlayState Init\n");
	ClearRequest();
    m_Exit = false;
	m_Enter = true;
	alpha = 255;

	Enemy::Init();
	EnemyBullet::Init();
	Item::Init();
	ScoreMSG::Init();
	
    stage = 1;
	player = new Player();
	level = new Level01();
	ui = new Interface();

	scan_timer.start();
	fade_timer.start();
}

void CPlayState::Cleanup()
{
	printf("CPlayState Cleanup\n");
    ClearObjects();
	delete level;
	delete ui;
	delete player;
}

CPlayState::~CPlayState()
{
    printf("delete playstate\n");
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
    //for (auto it = coinList.begin(); it != coinList.end();) {
    //    delete (*it);
    //    it++; }
    enemy_list.clear();
	pl_bulletlist.clear();
	en_bulletlist.clear();
    //coinList.clear();
}

void CPlayState::Pause()
{
	printf("CPlayState Pause\n");
}

void CPlayState::Resume()
{
	printf("CPlayState Resume\n");
	if (m_Exit)
	{
		m_Exit = false;
		alpha = 255;
		m_Enter = true;
	}
}

void CPlayState::Return()
{
	printf("CPlayState Return\n");

}

void CPlayState::NewLevel()
{

}

void CPlayState::CheckKeys(const KeyStruct& keys)
{
	player->CheckKeys(keys);
	if (keys.enter) m_Exit = true;
	if (keys.esc) PushState(S_PAUSE);
}

template <class T>
void CPlayState::UpdateList(std::list<T>& lst, const int& iElapsedTime)
{
	for (auto it = lst.begin(); it != lst.end();)
	{
		if ((*it)->RequestDelete())
		{
			delete (*it);
			it = lst.erase(it);	
		}
		else
		{
			(*it)->Update(iElapsedTime);
			it++;
		}
	}
}

void CPlayState::Update(const int& iElapsedTime)
{
	if (m_Enter)
	{
		if (alpha > 0) 
		{
			if (fade_timer.get_ticks() > 10) 
			{
				alpha-=5;
				fade_timer.start(); 
			} 
		}
		else
			m_Enter = false;
	}
	if (m_Exit)
	{
		if (alpha < 255) 
		{
			if (fade_timer.get_ticks() > 10) 
			{
				alpha+=5;
				fade_timer.start(); 
			} 
		}
		else
			PushState(S_POLL);
	}
	Camera::Update(player->GetOuterBounds().x, iElapsedTime);
	level->Update(iElapsedTime);
	level->LoadEnemies(enemy_list);
	player->Update(iElapsedTime);

	if (scan_timer.get_ticks() > 30)
	{
		for (auto it = pl_bulletlist.begin(); it != pl_bulletlist.end(); it++)
		{
			(*it)->DetectCollision();
		}
		scan_timer.start();
	}
	UpdateList(pl_bulletlist, iElapsedTime);
	UpdateList(en_bulletlist, iElapsedTime);
	UpdateList(enemy_list, iElapsedTime);
	UpdateList(item_list, iElapsedTime);
	UpdateList(score_list, iElapsedTime);

	ui->Update(iElapsedTime);
}

template <class T>
void CPlayState::DrawList(std::list<T>& lst, SDL_Surface* dest)
{
	for (auto it = lst.begin(); it != lst.end(); it++)
	{
		(*it)->Draw(dest);
	}
}

void CPlayState::Draw(SDL_Surface* dest)
{
	level->Draw(dest);

	DrawList(enemy_list, dest);
	DrawList(pl_bulletlist, dest);
	
	if (m_Exit)
		SPG_RectFilledBlend(dest,_G_BANNER_WIDTH,0,_G_BOUNDS_WIDTH,_WSCREEN_HEIGHT, 16777215, alpha);
	if (m_Enter)
		SPG_RectFilledBlend(dest,_G_BANNER_WIDTH,0,_G_BOUNDS_WIDTH,_WSCREEN_HEIGHT, 0, alpha);

	player->Draw(dest);

	DrawList(en_bulletlist, dest);
	DrawList(item_list, dest);
	DrawList(score_list, dest);

	ui->Draw(dest);
	
}