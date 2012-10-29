#include "Gem.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "Game/Interface.h"
#include "Game/Camera.h"
#include "Player/Player.h"
#include "Game/GameScore.h"
#include "UI/ScoreMsg.h"

Gem::Gem(int x, int y, int value, bool autoLocked) : Item(x, y, value, "Gem.png")
{
	mAir = true;
    mDelete = false;
	yvel = -200;
	mLockedOn = autoLocked;
	mClip = 0;
	mAccelTimer.Start();
}

Gem::~Gem() 
{
	if (pickedup)
	{
		GameScore::Instance()->IncreaseGemCount();
		GameScore::Instance()->IncreaseBonus();
		SFX::PlaySoundResource("gem_pickup.wav");
		//CPlayState::Instance()->scoreMsgList.push_back(new ScoreMSG(mX, mY, mSpawnSide, GameScore::Instance()->GetBonus() * val));
		CPlayState::Instance()->score_list.push_back(new ScoreMSG(mX, mY, mSpawnSide, val));
	}
}

void Gem::Update(Uint32 deltaTicks)
{
	if (pickedup) mDelete = true;
	Shared::CheckClip(mClipTimer, mClip, 50, mpInfo->maxClips, 0);

	SDL_Rect playerbox = CPlayState::Instance()->mpPlayer->GetOuterBounds().rect;
    float dx = (playerbox.x + playerbox.w/2) - (mOffset.x - Camera::CameraX()  + mOffset.w/2);
    float dy = (playerbox.y + playerbox.h/2) - (mOffset.y + mOffset.h/2);
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));

	if (Length > 0.1f && Length < 200 && !mLockedOn)
	{
		mLockedOn = true;
		mAccelTimer.Start();
	}

	if (CPlayState::Instance()->mpPlayer->IsExploding() )
		mLockedOn = false;

	if ((mLockedOn) && mDurationTimer.GetTicks() > 600)
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
		if (mDurationTimer.GetTicks() > 200) yvel+= 500 * deltaTicks/1000.f;
		mY += (yvel * (deltaTicks / 1000.f));
	}
	mOffset.x = mX;
    mOffset.y = mY;

    
	if (CheckOffscreen(mX, mY, mpInfo->height))
		mDelete = true;
}

void Gem::Draw(SDL_Surface *pDest)
{
    Camera::DrawSurface(mOffset.x, mOffset.y + Camera::CameraY2(),
        mpInfo->pSurface, pDest, &mpInfo->pClips[mClip]);
}