#include "Engine/Shared.h"
#include "Layer.h"
#include "Level01.h"
#include "Game/Camera.h"
#include "State/playstate.h"
#include "Enemy/Enemy.h"
#include "Enemy/Zown.h"

Level01::Level01()
{
    printf("Level01 initialize\n");

	/* initialize enemies used for this level */
	
	Zown::Init();

	/* Create layers used for this level */
	mpBackground = Shared::LoadImage("Image/Levels/level02.png");
	mpTopSurface = Shared::LoadImage("Image/Levels/fog.png");
	mpTop = new Layer(mpTopSurface, 600, 0);
	mpTop->Start();

	mLevelEnd = 6400;
	Camera::Reset();

	for (int i=6500; i>0; i-=100)
		enemy_cache.push_back(new Zown(GAME_LEVEL_WIDTH/2,i));
}

void Level01::LoadEnemies(std::list<Enemy*>& rList)
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

Level01::~Level01()
{
	printf("Level01 Cleanup\n");
	SDL_FreeSurface(mpBackground);
	SDL_FreeSurface(mpTopSurface);
	enemy_cache.clear();
	Zown::Cleanup();
	/* CleanUp enemies used for this level */
	//
	//

	//delete layers
}

void Level01::Update(const int& rDeltaTime)
{
	mpTop->Update(rDeltaTime, Camera::CameraSpeed()*3);
	mBounds.x = Camera::CameraX();
	mBounds.y = Camera::CameraY2() - WINDOW_HEIGHT;
}

void Level01::Draw(SDL_Surface *pDest)
{
	Shared::DrawSurface(GAME_BANNER_WIDTH, 0, mpBackground, pDest, &mBounds);

	mpTop->Draw(pDest);
}