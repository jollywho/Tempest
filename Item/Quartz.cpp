#include "Quartz.h"
#include "Engine/SpriteResource.h"
#include "Game/Interface.h"
#include "Game/Gamescore.h"
#include "Game/Camera.h"
#include "State/playstate.h"
#include "Player/Player.h"
#include "UI/ScoreMSG.h"

Quartz::Quartz(int x, int y, int value) : Item(x, y, 1000, "quartz")
{
	mAir = false;
    mDelete = false;
	mLockedOn = false;
	mClip = 0;
}

Quartz::~Quartz() 
{
	if (pickedup)
	{
		GameScore::Instance()->IncreaseQuartzCount();
		CPlayState::Instance()->score_list.push_back(new ScoreMSG(mX, mY - Camera::Instance()->CameraY2(), mSpawnSide, GameScore::Instance()->GetBonus() * val));
	}
}

void Quartz::Update(Uint32 deltaTicks)
{
	if (pickedup) mDelete = true;
	Shared::CheckClip(mClipTimer, mClip, 50, mpInfo->maxClips, 0);
	SDL_Rect playerbox = CPlayState::Instance()->mpPlayer->GetOuterBounds().rect;
    float dx = (playerbox.x + playerbox.w/2) - (mOffset.x - Camera::Instance()->CameraX()  + mOffset.w/2);
    float dy = (playerbox.y + playerbox.h/2) - (mOffset.y - Camera::Instance()->CameraY2() + mOffset.h/2);
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));

	if (Length > 0.1f && Length < 100 && mDurationTimer.GetTicks() > 600 && !mLockedOn)
	{
		mLockedOn = true;
		mAccelTimer.Start();
	}

	if (mLockedOn)
	{
		float xa = dx / Length;
		float ya = dy / Length;
		yvel+=mAccelTimer.GetTicks()/50;
		mX += (xa * (yvel * (deltaTicks / 1000.f)));
		mY += (ya * (yvel * (deltaTicks / 1000.f)));
		CheckCollision();
	}
	else
	{
		mY += (yvel * (deltaTicks / 1000.f));
	}
	mOffset.x = mX;
    mOffset.y = mY;

    
	if (CheckOffscreen(mX, mY - Camera::Instance()->CameraY2(), mpInfo->height))
		mDelete = true;
}

void Quartz::Draw(SDL_Surface *pDest)
{
    Camera::Instance()->DrawSurface(mOffset.x, mOffset.y,
        mpInfo->pSurface, pDest, &mpInfo->pClips[mClip]);
}