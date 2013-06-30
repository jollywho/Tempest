#include "Coin.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "Game/Interface.h"
#include "Game/Camera.h"
#include "Player/Player.h"
#include "Game/GameScore.h"
#include "UI/ScoreMsg.h"

Coin::Coin(int x, int y, int value) : Item(x, y, value, "Coin.png")
{
	mAir = true;
    mDelete = false;
	yvel = 250;
	mClip = 0;
	mAccelTimer.Start();
}

Coin::~Coin() 
{
	if (pickedup)
	{
		GameScore::Instance()->IncreaseCoinCount();
		GameScore::Instance()->IncreaseBonus();
		SFX::PlaySoundResource("coin_pickup.wav");
		//CPlayState::Instance()->scoreMsgList.push_back(new ScoreMSG(mX, mY, mSpawnSide, GameScore::Instance()->GetBonus() * val));
		CPlayState::Instance()->score_list.push_back(new ScoreMSG(mX, mY, mSpawnSide, val));
	}
}

void Coin::Update(Uint32 deltaTicks)
{
	if (pickedup) mDelete = true;
	Shared::CheckClip(mClipTimer, mClip, 60, mpInfo->maxClips, 0);
	CheckCollision();

	mY += (yvel * (deltaTicks / 1000.f));

	mOffset.x = mX;
    mOffset.y = mY;
    
	if (CheckOffscreen(mX, mY, mpInfo->height))
		mDelete = true;
}

void Coin::Draw(SDL_Surface *pDest)
{
    Camera::Instance()->DrawSurface(mOffset.x, mOffset.y + Camera::Instance()->CameraY2(),
        mpInfo->pSurface, pDest, &mpInfo->pClips[mClip]);
}