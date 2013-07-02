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

Enemy::Enemy(int x, int y, int hp, std::string id, std::list<Action*>& actions)
{
	printf("Enemy Created\n");

	mpInfo = &SpriteResource::RequestResource("Enemies", id);
	mClipTimer.Start();

	mBombupSpawn = false;
	mPowerupSpawn = false;
    mDelete = false;
    mExplode = false;
    mHit = false;
	mClip = 0;
	mX = x - mpInfo->width/2; 
	mY = y - mpInfo->height/2;
	mHitbox.x = mX; 
	mHitbox.y = mY;
	mHitbox.w = mpInfo->width; 
	mHitbox.h = mpInfo->height;
	mHealth = hp;
	mMaxHealth = hp;

	std::copy( actions.begin(), actions.end(), std::back_inserter( mActions ) );
	mDo = mActions.begin();
}

void Enemy::Init()
{
    mspHitSurface = Shared::LoadImage("Image/Enemies/HitColor.png");
}

void Enemy::Cleanup()
{
    SDL_FreeSurface(mspHitSurface);
}

void Enemy::Decide(Uint32 deltaTicks)
{
	if ((*mDo)->RequestNext())
		++mDo;
		if (mDo == mActions.end())
			mDo = mActions.begin();
	(*mDo)->Update(*this, deltaTicks);
}

void Enemy::FlashRed(SDL_Surface* en_surface, SDL_Rect* targetClip)
{
    if (!mHit)
    {
		SFX::PlaySoundResource("en_takehit.wav");
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
	if( mY + mpInfo->height - Camera::Instance()->CameraY2() > 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::MoveTo(Point p)
{
	mDest = p;
	mVel.x = ((rand() % 100) - 50);
	mVel.y = -10 * (rand() % 10);
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
			CPlayState::Instance()->item_list.push_back(new Bombup(mX + mpInfo->width/2, mY + mpInfo->height/2, 0));
		else if (mPowerupSpawn)
			CPlayState::Instance()->item_list.push_back(new Powerup(mX + mpInfo->width/2, mY + mpInfo->height/2, 0));
		else
		{
			for (int i=0; i<=mMaxHealth; i+=25)
				CPlayState::Instance()->item_list.push_back(
				new Gem(mX + rand() % mpInfo->width, mY + mpInfo->height/2, 25));
		}
		Explosion::RequestExplosion(mId, mX + mpInfo->width/2, mY + mpInfo->height/2, 0, 10);
		SFX::PlaySoundResource("explode_light1.wav");
		mExplode = true;
	}
	return false;
}

void Enemy::DetectCollision()
{
	if( mY - Camera::Instance()->CameraY2() > GAME_BOUNDS_HEIGHT)
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