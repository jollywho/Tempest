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

	/* initialize enemies used for this level */

	/* Create layers used for this level */
	mpBackground = Shared::LoadImage("Image/Levels/level02.png");
	mpTopSurface = Shared::LoadImage("Image/Levels/fog.png");
	mpTop = new Layer(mpTopSurface, 720, 0);
	mpTop->Start();

	mLevelEnd = 6400;
	Camera::Instance()->Reset();
	GameScore::Instance()->ResetLevel();
	
	Factory::ReadFile("Script/level_01.dat", enemy_cache);
}

//Load onscreen enemies from the cache to the active list.
void Level::LoadEnemies(std::list<Enemy*>& rList)
{
	for (auto it = enemy_cache.begin(); it != enemy_cache.end();)
	{
		if ((*it)->CheckBounds())
		{
			rList.push_back((*it));
			it = enemy_cache.erase(it);
		}
		else
			it++;
	}
}

Level::~Level()
{
	printf("Level01 Cleanup\n");
	SDL_FreeSurface(mpBackground);
	SDL_FreeSurface(mpTopSurface);
	for (auto it = enemy_cache.begin(); it != enemy_cache.end();) {
        delete (*it);
        it++; }
	enemy_cache.clear();
}

void Level::Update(const int& rDeltaTime)
{
	mpTop->Update(rDeltaTime, Camera::Instance()->CameraSpeed()*3);
	mBounds.x = Camera::Instance()->CameraX();
	mBounds.y = Camera::Instance()->CameraY2() - WINDOW_HEIGHT;
}

void Level::Draw(SDL_Surface *pDest)
{
	Shared::DrawSurface(GAME_BANNER_WIDTH, 0, mpBackground, pDest, &mBounds);

	mpTop->Draw(pDest);
}