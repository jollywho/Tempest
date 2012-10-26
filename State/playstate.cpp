#include "playstate.h"
#include "Game/Camera.h"
#include "Game/Interface.h"
#include "Level/Level01.h"
#include "Enemy/Enemy.h"

CPlayState CPlayState::m_PlayState;
bool CPlayState::m_Exit = false;

#pragma region INIT
void CPlayState::Init()
{
	printf("CPlayState Init\n");
    m_Exit = false;
	
    stage = 1;
	player = new Player();
	level = new Level01();
	ui = new Interface();
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
    //for (auto it = coinList.begin(); it != coinList.end();) {
    //    delete (*it);
    //    it++; }
    enemy_list.clear();
	pl_bulletlist.clear();
    //coinList.clear();
}

void CPlayState::Pause()
{
	printf("CPlayState Pause\n");
}

void CPlayState::Resume()
{
	printf("CPlayState Resume\n");
}

void CPlayState::NewLevel()
{

}

void CPlayState::CheckKeys(const KeyStruct& keys)
{
	player->CheckKeys(keys);
}

template <class T>
void CPlayState::UpdateList(std::list<T>& lst, const int& iElapsedTime)
{
	for (auto it = lst.begin(); it != lst.end();)
	{
		(*it)->Update(iElapsedTime);
		if ((*it)->RequestDelete())
		{
			delete (*it);
			it = lst.erase(it);	
		}
		else
		{
			it++;
		}
	}
}

void CPlayState::Update(const int& iElapsedTime)
{
	Camera::Update(player->GetOuterBounds().x, iElapsedTime);
	level->Update(iElapsedTime);
	player->Update(iElapsedTime);

	UpdateList(pl_bulletlist, iElapsedTime);
	UpdateList(enemy_list, iElapsedTime);

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

	player->Draw(dest);

	ui->Draw(dest);
}