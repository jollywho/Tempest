#include "Engine/Shared.h"
#include "Layer.h"
#include "Level01.h"
#include "Game/Camera.h"
#include "State/playstate.h"
#include "Enemy/Enemy.h"
#include "Enemy/Zown.h"

Level01::Level01()
{
    printf("Level01 Init\n");

	/* Init enemies used for this level */
	
	Zown::Init();

	/* Create layers used for this level */
	bg = Shared::load_image("Image/Levels/level02.png");
	top_surface = Shared::load_image("Image/Levels/fog.png");
	top = new Layer(top_surface, 600, 0);
	top->Start();

	levelend = 6400;
	Camera::Reset();

	for (int i=6500; i>0; i-=100)
		enemy_cache.push_back(new Zown(_G_LEVEL_WIDTH/2,i));
}

void Level01::LoadEnemies(std::list<Enemy*>& lst)
{
	for (auto it = enemy_cache.begin(); it != enemy_cache.end();)
	{
		if ((*it)->CheckBounds())
		{
			lst.push_back((*it));
			it = enemy_cache.erase(it);
		}
		else
			it++;
	}
}

Level01::~Level01()
{
	printf("Level01 Cleanup\n");
	SDL_FreeSurface(bg);
	SDL_FreeSurface(top_surface);
	enemy_cache.clear();
	Zown::CleanUp();
	/* CleanUp enemies used for this level */
	//
	//

	//delete layers
}

void Level01::Update(const int& iElapsedTime)
{
	top->Update(iElapsedTime, Camera::CameraSpeed()*3);
	bounds.x = Camera::CameraX();
	bounds.y = Camera::CameraY2() - _WSCREEN_HEIGHT;
}

void Level01::Draw(SDL_Surface *dest)
{
	Shared::apply_surface(_G_BANNER_WIDTH, 0, bg, dest, &bounds);

	top->Draw(dest);
}