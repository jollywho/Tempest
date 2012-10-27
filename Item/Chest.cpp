#include "Chest.h"
#include "Gem.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "Game/Interface.h"
#include "Player/Player.h"
#include "Game/GameScore.h"
#include "Game/Camera.h"

Chest::Chest(int x, int y, int value) : Item(x, y, value, "Chest.png")
{
	Air = false;
    m_delete = false;
	opened = false;
	clip = 0;
	spawnCount = 0;
}

Chest::~Chest() 
{
}

void Chest::Update(Uint32 deltaTicks)
{
	Check_Collision();
	if (pickedup)
	{
		Shared::CheckClip(clip_Timer, clip, 50, _info->clip_count, _info->clip_count-1);

		if (clip == _info->clip_count-1 && !opened) 
		{ 
			opened = true;
			spawn_Timer.start();
		}

		if (spawnCount < 10 && spawn_Timer.get_ticks() > 100)
		{
			spawn_Timer.start();
			CPlayState::Instance()->item_list.push_back(new Gem(xVal + _info->width/2, yVal, 825));
			spawnCount++;
		}
	}
    
	//if (CheckOffscreen(xVal, yVal + Camera::CameraY2, _info->height))
	//	m_delete = true;
}

void Chest::Draw(SDL_Surface *dest)
{
    Camera::DrawSurface(offset.x, offset.y,
        _info->surface, dest, &_info->clips[clip]);
}