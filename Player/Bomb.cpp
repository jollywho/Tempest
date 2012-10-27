#include "Bomb.h"
#include "Engine/SpriteResource.h"
#include "Game/Camera.h"
#include "State/Playstate.h"
#include "Pattern/EnemyBullet.h"
#include "Enemy/Enemy.h"

SpriteInfo* Bomb::sprite;

Bomb::Bomb()
{
	printf("Bomb created\n");
	active = false;
	SpriteResource::AddResource("Player", "bomb.png", 192, 192, 60, 24);
	sprite = &SpriteResource::RequestResource("Player", "bomb.png");
}

Bomb::~Bomb()
{
	//anything done here?
}

void Bomb::Start(int x, int y)
{
	xVal = x - sprite->width/2 + Camera::CameraX();
	yVal = y - sprite->height*2 + Camera::CameraY2();

	/* Always have bomb visible on screen */
	//todo: have bomb movement and wall collision
	//issue: camera throws these values off
	if (xVal < _G_BANNER_WIDTH) xVal = _G_BANNER_WIDTH + 20;
	if (xVal + sprite->width > _G_LEVEL_WIDTH) xVal = _G_LEVEL_WIDTH - sprite->width - 20;
	//if (yVal < _G_UI_HEIGHT) yVal = _G_UI_HEIGHT + 20;
	//if (yVal + sprite->height > _G_UI_BOTTOM) yVal = _G_UI_BOTTOM - sprite->height - 20;

	active = true;
	clip = 0;
	dps_timer.start();
	clip_timer.start();
}

void Bomb::Update(const int& iElapsedTime)
{
	if (!active) return;
	if (clip >= sprite->clip_count) active = false;
	Shared::CheckClip(clip_timer, clip, sprite->interval, sprite->clip_count, sprite->clip_count);

    for (auto it = CPlayState::Instance()->en_bulletlist.begin(); it != CPlayState::Instance()->en_bulletlist.end(); it++)
        (*it)->Destroy();

    if (dps_timer.get_ticks() > 60)
    {
        for (auto it = CPlayState::Instance()->enemy_list.begin(); it != CPlayState::Instance()->enemy_list.end();it++)
            (*it)->TakeHit(1);
		dps_timer.start();
    }
}

void Bomb::Draw(SDL_Surface *dest)
{
	if (!active) return;
	Camera::DrawSurface(xVal, yVal, sprite->surface, dest, &sprite->clips[clip]);
}