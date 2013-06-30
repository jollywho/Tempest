#include "Engine/Shared.h"
#include "Layer.h"
#include "Level.h"
#include "Game/Camera.h"
#include "State/playstate.h"
#include "Game/GameScore.h"
#include "Enemy/Enemy.h"
#include "Enemy/Zown.h"

Level::Level()
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
	GameScore::Instance()->ResetLevel();

	lua_register(CEngine::mspL, "loadstuff", loadstuff);
	luaL_dofile(CEngine::mspL, "Level01.lua");

	for (int i=6500; i>0; i-=100)
		enemy_cache.push_back(new Zown(GAME_LEVEL_WIDTH/2,i));
}

int Level::loadstuff(lua_State *L)
{
	return 0;
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
	enemy_cache.clear();
	Zown::Cleanup();
	/* CleanUp enemies used for this level */
	//
	//

	//delete layers
}

void Level::Update(const int& rDeltaTime)
{
	mpTop->Update(rDeltaTime, Camera::CameraSpeed()*3);
	mBounds.x = Camera::CameraX();
	mBounds.y = Camera::CameraY2() - WINDOW_HEIGHT;
}

void Level::Draw(SDL_Surface *pDest)
{
	Shared::DrawSurface(GAME_BANNER_WIDTH, 0, mpBackground, pDest, &mBounds);

	mpTop->Draw(pDest);
}