#include "Enemy.h"
#include "Game/Camera.h"
#include "Engine/SpriteResource.h"
#include "Player/Player.h"
#include "State/Playstate.h"
#include "Item/Gem.h"
#include "Item/Powerup.h"
#include "Item/Bombup.h"
#include "Game/GameScore.h"
#include "Engine/SFX.h"
#include "Pattern/Explosion.h"
#include "Action/Action.h"

SDL_Surface* Enemy::mspHitSurface;
SDL_Color Enemy::msHitColor = { 255, 0, 0 };

Enemy::Enemy(std::string id, int x, int y, std::list<Action*>& actions)
{
	printf("Enemy Created\n");

	mId = id;
	mpInfo = &SpriteResource::RequestResource("Enemy", id);
	mClipTimer.Start();
	
	mBombupSpawn = false;
	mPowerupSpawn = false;
    mDelete = false;
    mExplode = false;
    mHit = false;
	mClip = 0;
	mPos.x = x - mpInfo->width/2; 
	mPos.y = y - mpInfo->height/2;
	mHitbox.x = mPos.x; 
	mHitbox.y = mPos.y;
	mHitbox.w = mpInfo->width; 
	mHitbox.h = mpInfo->height;

	std::copy( actions.begin(), actions.end(), std::back_inserter( mActions ) );
	mDo = mActions.begin();
}

Enemy::~Enemy()
{
	for (auto it = mActions.begin(); it != mActions.end();) {
    delete (*it);
    it++; }
}

void Enemy::Init()
{
    mspHitSurface = Shared::LoadImage("Image/Enemy/HitColor.png");
}

void Enemy::Cleanup()
{
    SDL_FreeSurface(mspHitSurface);
}

void Enemy::Decide(Uint32 deltaTicks)
{
	if (mActions.size() < 1) return;

    if ((*mDo)->RequestNext()) { ++mDo; }
    if (mDo == mActions.end()) { mDo = mActions.begin(); }

	if ((*mDo)->IsLoopAction())
    {
        int counter = 0;
        int max = (*mDo)->ActionCount();
        for (int i=0; i < max; i++)
        {
            mDo = std::next(mActions.begin(), + i);
            (*mDo)->Update(*this, deltaTicks);
            counter += (*mDo)->RequestNext();
            if (counter > max)
            {
                mDo = std::prev (mActions.end(), counter);
            }
        }
    }
    else
        (*mDo)->Update(*this, deltaTicks);
}

void Enemy::FlashRed(SDL_Surface* en_surface, SDL_Rect* targetClip)
{
    if (!mHit)
    {
		SFX::PlaySoundResource("en_takehit");
		GameScore::Instance()->IncreaseScore(1);
		mHit = true;
		mHitTimer.Start();
		mpCopySurface = SDL_ConvertSurface(en_surface, en_surface->format, SDL_SWSURFACE);
		Shared::DrawSurface(targetClip->x, targetClip->y, mspHitSurface, mpCopySurface, NULL);
    }
}

void Enemy::FlashClear()
{
	if (mHit && mHitTimer.GetTicks() > 30)
	{
		mHit = false;
		SDL_FreeSurface(mpCopySurface);
	}
}

bool Enemy::CheckBounds()
{
	if( mPos.y + mpInfo->height - Camera::Instance()->CameraY2() > 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::Movement(const float& x, const float& y)
{
	mPos.x += x; mPos.y += y;
}

bool Enemy::Explode(bool del)
{
	if (mExplode)
	{
		mDelete = del;
		return true;
	}
	else
		return false;
}

bool Enemy::CheckHealth()
{
	FlashClear();
	if (mHealth <= 0)
	{
		if (mBombupSpawn)
			CPlayState::Instance()->item_list.push_back(new Bombup(mPos.x + mpInfo->width/2, mPos.y + mpInfo->height/2, 0));
		else if (mPowerupSpawn)
			CPlayState::Instance()->item_list.push_back(new Powerup(mPos.x + mpInfo->width/2, mPos.y + mpInfo->height/2, 0));
		else
		{
			for (int i=0; i<=mMaxHealth; i+=25)
				CPlayState::Instance()->item_list.push_back(
				new Gem(mPos.x + rand() % mpInfo->width, mPos.y + mpInfo->height/2, 25));
		}
		Explosion::RequestExplosion(mId, mPos.x + mpInfo->width/2, mPos.y + mpInfo->height/2, 0, 10);
		SFX::PlaySoundResource("explode_light1");
		mExplode = true;
	}
	return false;
}

void Enemy::DetectCollision()
{
	if( mPos.y - Camera::Instance()->CameraY2() > GAME_BOUNDS_HEIGHT)
	{
		mDelete = true;
		return;
	}

	SDL_Rect pl_mpHitbox = CPlayState::Instance()->mpPlayer->GetBounds().rect;

	
	if (mHitbox.x + mHitbox.w > pl_mpHitbox.x  && 
        mHitbox.x < pl_mpHitbox.x + pl_mpHitbox.w  && 
        mHitbox.y + mHitbox.h > pl_mpHitbox.y && 
        mHitbox.y < pl_mpHitbox.y + pl_mpHitbox.h)
        { 
            TakeHit(1);
			CPlayState::Instance()->mpPlayer->TakeHit();
		}
}