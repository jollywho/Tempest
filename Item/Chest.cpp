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
	mAir = false;
    mDelete = false;
	opened = false;
	mClip = 0;
	spawnCount = 0;
}

Chest::~Chest() 
{
}

void Chest::Update(Uint32 deltaTicks)
{
	CheckCollision();
	if (pickedup)
	{
		Shared::CheckClip(mClipTimer, mClip, 50, mpInfo->maxClips, mpInfo->maxClips-1);

		if (mClip == mpInfo->maxClips-1 && !opened) 
		{ 
			opened = true;
			spawn_Timer.Start();
		}

		if (spawnCount < 10 && spawn_Timer.GetTicks() > 100)
		{
			spawn_Timer.Start();
			CPlayState::Instance()->item_list.push_back(new Gem(mX + mpInfo->width/2, mY, 825));
			spawnCount++;
		}
	}
    
	//if (CheckOffscreen(mX, mY + Camera::CameraY2, mpInfo->height))
	//	mDelete = true;
}

void Chest::Draw(SDL_Surface *pDest)
{
    Camera::DrawSurface(mOffset.x, mOffset.y,
        mpInfo->pSurface, pDest, &mpInfo->pClips[mClip]);
}