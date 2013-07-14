#include "Bomb.h"
#include "Engine/SpriteResource.h"
#include "Engine/SFX.h"
#include "Game/Camera.h"
#include "State/Playstate.h"
#include "Pattern/EnemyBullet.h"
#include "Enemy/Enemy.h"

SpriteInfo* Bomb::mpSprite;

Bomb::Bomb()
{
	printf("Bomb created\n");
	mActive = false;
	mpSprite = &SpriteResource::RequestResource("Player", "bomb");
}

Bomb::~Bomb()
{
	//anything done here?
}

void Bomb::Start(int x, int y)
{
	mX = x - mpSprite->width/2 + Camera::Instance()->CameraX();
	mY = y - mpSprite->height*2 + Camera::Instance()->CameraY2();

	/* Always have bomb visible on screen */
	//todo: have bomb movement and wall collision
	//issue: camera throws these values off
	SFX::PlaySoundResource("bomb");
	Camera::Instance()->StartShake(4);
	if (mX < GAME_BANNER_WIDTH) mX = GAME_BANNER_WIDTH + 20;
	if (mX + mpSprite->width > GAME_LEVEL_WIDTH) mX = GAME_LEVEL_WIDTH - mpSprite->width - 20;
	//if (mY < GAME_UI_TOP) mY = GAME_UI_TOP + 20;
	//if (mY + sprite->height > GAME_UI_BOTTOM) mY = GAME_UI_BOTTOM - sprite->height - 20;

	mActive = true;
	mClip = 0;
	dps_timer.Start();
	mClipTimer.Start();
}

void Bomb::BulletWipe()
{
	for (auto it = CPlayState::Instance()->en_bulletlist.begin(); it != CPlayState::Instance()->en_bulletlist.end(); it++)
        (*it)->Destroy();
}

void Bomb::Update(const int& rDeltaTime)
{
	if (!mActive) return;
	
	if (mClip == mpSprite->maxClips/2)
		SFX::PlaySoundResource("bomb2");
	Shared::CheckClip(mClipTimer, mClip, mpSprite->interval, mpSprite->maxClips, mpSprite->maxClips);
	if (mClip >= mpSprite->maxClips) mActive = false;

	for (auto it = CPlayState::Instance()->en_bulletlist.begin(); it != CPlayState::Instance()->en_bulletlist.end(); it++)
        (*it)->Destroy();

    if (dps_timer.GetTicks() > 60)
    {
        for (auto it = CPlayState::Instance()->enemy_list.begin(); it != CPlayState::Instance()->enemy_list.end();it++)
            (*it)->TakeHit(1);
		dps_timer.Start();
    }
}

void Bomb::Draw(SDL_Surface *pDest)
{
	if (!mActive) return;
	Camera::Instance()->DrawSurface(mX, mY, mpSprite->pSurface, pDest, &mpSprite->pClips[mClip]);
}