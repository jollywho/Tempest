#include "Powerup.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "Game/Interface.h"
#include "Game/Camera.h"
#include "Player/Player.h"
#include "Game/GameScore.h"

Powerup::Powerup(int x, int y, int value) : Item(x, y, value, "Powerup.png")
{
	mAir = true;
	mpPickup = &SpriteResource::RequestResource("Items", "Powerup_Received.png");
    mDelete = false;
	yvel = 200 * ((rand() % 2) == 1 ? -1 : 1);
	xvel = 200 * ((rand() % 2) == 1 ? -1 : 1);
}

Powerup::~Powerup() 
{

}

void Powerup::Update(Uint32 deltaTicks)
{
	if (pickedup)
	{
		Shared::CheckClip(mClipTimer, mClip, mpPickup->interval, mpPickup->maxClips, 0);
		if (!received) 
		{
			SFX::PlaySoundResource("powerup_pickup.wav");
			received = true;
			mDurationTimer.Start(); 
			CPlayState::Instance()->mpPlayer->WeaponLevelUp();
			yvel = -100;
			xvel = 0;
		}
		if (mDurationTimer.GetTicks() > 1000)
			mDelete = true;
	}
	else 
	{
		Shared::CheckClip(mClipTimer, mClip, 50, mpInfo->maxClips, 0);
		CheckCollision();
		CheckWallCollision(mpInfo->width, mpInfo->height);
	}
	
	mX += (xvel * (deltaTicks / 1000.f));
	mY += (yvel * (deltaTicks / 1000.f));

	mOffset.x = mX;
    mOffset.y = mY;
}

void Powerup::Draw(SDL_Surface *pDest)
{
	if (pickedup) {
		Camera::Instance()->DrawSurface(mOffset.x - 45, mOffset.y + Camera::Instance()->CameraY2() - 25,
			smpPickupFrameInfo, pDest, NULL);
		Camera::Instance()->DrawSurface(mOffset.x, mOffset.y + Camera::Instance()->CameraY2(),
			mpPickup->pSurface, pDest, &mpPickup->pClips[mClip]);
	}
	else
		Camera::Instance()->DrawSurface(mOffset.x, mOffset.y + Camera::Instance()->CameraY2(),
			mpInfo->pSurface, pDest, &mpInfo->pClips[mClip]);
}