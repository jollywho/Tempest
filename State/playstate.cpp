#include "playstate.h"
#include "Game/Camera.h"
#include "Game/Interface.h"
#include "Level/Level01.h"

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
	for (auto it = pl_bulletlist.begin(); it != pl_bulletlist.end();) {
		delete (*it);
		it++; }
	pl_bulletlist.clear();
}

CPlayState::~CPlayState()
{
    printf("delete playstate\n");
}

void CPlayState::ClearObjects()
{
    //for (auto it = enemyList.begin(); it != enemyList.end();) {
    //    delete (*it);
    //    it++; }
    //for (auto it = bulletlist.begin(); it != bulletlist.end();) {
    //    delete (*it);
    //    it++; }
    //for (auto it = coinList.begin(); it != coinList.end();) {
    //    delete (*it);
    //    it++; }
    //enemyList.clear();
    //bulletlist.clear();
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

void CPlayState::Update(const int& iElapsedTime)
{
	Camera::Update(player->GetOuterBounds().x, iElapsedTime);
	level->Update(iElapsedTime);
	player->Update(iElapsedTime);


	for (auto it = pl_bulletlist.begin(); it != pl_bulletlist.end();)
	{
		(*it)->Update(iElapsedTime);
		if ((*it)->RequestDelete())
		{
			delete (*it);
			it = pl_bulletlist.erase(it);	
		}
		else
		{
			it++;
		}
	}

	ui->Update(iElapsedTime);
}

void CPlayState::Draw(SDL_Surface* dest)
{
	level->Draw(dest);

	for (auto it = pl_bulletlist.begin(); it != pl_bulletlist.end(); it++)
	{
		(*it)->Draw(dest);
	}

	player->Draw(dest);

	ui->Draw(dest);
}