#include "Engine/Shared.h"
#include "Layer.h"
#include "Level01.h"
#include "Game/Camera.h"

Level01::Level01()
{
    printf("Level01 Init\n");

	/* Init enemies used for this level */
    //Enemy::Init();
    //Gulm::Init();
    //Fazzle::Init();
    //Bat::Init();
    //Flamelord::Init();
    //CharDrgn::Init();

	//create layers

	//#include enemy spawns in file...??
	bg = Shared::load_image("Image/Levels/level02.png");
	top_surface = Shared::load_image("Image/Levels/fog.png");
	
	//bg = new Layer(bg_surface, 6400, );
	levelend = 6400;
	Camera::Reset();
	
}

Level01::~Level01()
{
	printf("Level01 Cleanup\n");
	SDL_FreeSurface(bg);
	SDL_FreeSurface(top_surface);
	/* CleanUp enemies used for this level */
	//
	//

	//delete layers
}

void Level01::Update(const int& iElapsedTime)
{
	//bg->Update(iElapsedTime, Camera::CameraSpeed());
	bounds.x = Camera::CameraX();
	bounds.y = Camera::CameraY2() - _WSCREEN_HEIGHT;
}

void Level01::Draw(SDL_Surface *dest)
{
	//bg->Draw(dest);
	Shared::apply_surface(_G_BANNER_WIDTH, 0, bg, dest, &bounds);
}