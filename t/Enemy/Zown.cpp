#include "Zown.h"
#include "Engine/SpriteResource.h"
#include "Game/Camera.h"
#include "Pattern/Explosion.h"
#include "Engine/Engine.h"

REGISTERIMPL(Zown);

Zown::Zown(int x, int y, std::list<Action*>& actions) : Enemy("zown", x, y, actions)
{
	mHealth = 50;
	mMaxHealth = 50;
	mAir = true;
    rot = 0; attackCount = 0;
	attack_Timer.Start();
	mVel = Point(0,0);
	mDest = Point(0,0);
}

Zown::~Zown()
{
    if (mHit)
        SDL_FreeSurface(mpCopySurface);
}

void Zown::TakeHit(int dmg)
{
    mHealth -= dmg;
    FlashRed(mpInfo->pSurface, &mpInfo->pClips[mClip]);
}

void Zown::Init()
{
	printf("Zown initialize\n");
	Explosion::AddExplosionInfo("Zown", "green_small1.png", 1, 0);
	Explosion::AddExplosionInfo("Zown", "green_small1.png", 1, 200, -50);
	Explosion::AddExplosionInfo("Zown", "green_small1.png", 1, 200, 50);
	Explosion::AddExplosionInfo("Zown", "green_small1.png", 5, 500, 50, 50);
	Explosion::AddExplosionInfo("Zown", "green_small1.png", 5, 1200, 50, -50);
}

void Zown::Cleanup()
{

}

void Zown::Attack()
{
	//CPlayState::Instance()->en_bulletlist.push_back(new ERotBullet(mX + mpInfo->width/2, mY + mpInfo->height, 0, "Arrow.png"));
	attack_Timer.Start();


	attackCount++;
	
	if (attackCount > 3) attackCount = 1;

	rot += .4;
	if (rot > M_PI)
		rot = 0;
	
	/*
	for (double i=0-rot; i<=M_PI/2+rot - .4; i+= .4 )
    {
        double x = cos(i);
        double y = sin(i);
        CPlayState::Instance()->en_bulletlist.push_back(new ERotBullet(atkgatset.x + GATE_WIDTH/2,
			atkgateLE.y + GATE_WIDTH/2,
			x*100, y * 100, "LargeRed.png"));

		CPlayState::Instance()->en_bulletlist.push_back(new ERotBullet(atkgateRIt.x + GATE_WIDTH/2,
			atkgateRIGHset.y + GATE_WIDTH/2,
			-x*100, y * 100, "LargeRed.png"));
    }
	*/
    attack_Timer.Start();

}

void Zown::Update(Uint32 deltaTicks)
{
	Decide(deltaTicks);
	if (Explode(true)) return;
	if (CheckHealth()) return;
	DetectCollision();

    if (attack_Timer.GetTicks() > 480)
        Attack();
	Shared::CheckClip(mClipTimer, mClip, mpInfo->interval, mpInfo->maxClips, 0);
	
	mX += mVel.x * (deltaTicks/1000.f);
	mY += mVel.y * (deltaTicks/1000.f);

    mHitbox.x = mX ;
    mHitbox.y = mY ;
}

void Zown::Draw(SDL_Surface *pDest)
{
	if (mExplode) return;

    if (mHit)
        Camera::Instance()->DrawSurface(mHitbox.x, mHitbox.y,
            mpCopySurface, pDest, &mpInfo->pClips[mClip]);
    else
        Camera::Instance()->DrawSurface(mHitbox.x, mHitbox.y,
            mpInfo->pSurface, pDest, &mpInfo->pClips[mClip]);
}