#include "Bombup.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "Game/GameScore.h"
#include "Game/Camera.h"
#include "Player/Player.h"

Bombup::Bombup(int x, int y, int value) : Item(x, y, value, "bombup.png")
{
	_received = &SpriteResource::RequestResource("Items", "Bombup_Received.png");
	mAir = true;
    mDelete = false;
	yvel = 200 * ((rand() % 2) == 1 ? -1 : 1);
	xvel = 200 * ((rand() % 2) == 1 ? -1 : 1);
}

Bombup::~Bombup() 
{
}

void Bombup::Update(Uint32 deltaTicks)
{
	if (pickedup)
	{
		Shared::CheckClip(mClipTimer, mClip, _received->interval, _received->maxClips, _received->maxClips-1);
		if (!received) 
		{
			SFX::PlaySoundResource("Bombup_pickup.wav");
			received = true;
			mDurationTimer.Start(); 
			GameScore::Instance()->IncreaseBombups();
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

void Bombup::Draw(SDL_Surface *pDest)
{
	if (pickedup) {
		Camera::DrawSurface(mOffset.x - 50, mOffset.y + Camera::CameraY2() - 25,
			received_frame, pDest, NULL);
		Camera::DrawSurface(mOffset.x, mOffset.y + Camera::CameraY2(),
			_received->pSurface, pDest, &_received->pClips[mClip]);
	}
	else
		Camera::DrawSurface(mOffset.x, mOffset.y + Camera::CameraY2(),
			mpInfo->pSurface, pDest, &mpInfo->pClips[mClip]);
}