#include "playstate.h"

CPlayState CPlayState::m_PlayState;
bool CPlayState::m_Exit = false;

#pragma region INIT
void CPlayState::Init()
{
	printf("CPlayState Init\n");
    m_Exit = false;
	
    stage = 1;
	player = new Player();

}

void CPlayState::Cleanup()
{
	printf("CPlayState Cleanup\n");
    ClearObjects();

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
	player->Update(iElapsedTime);
}

void CPlayState::Draw(SDL_Surface* dest)
{
	player->Draw(dest);
}