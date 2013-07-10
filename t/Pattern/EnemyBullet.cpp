#include "EnemyBullet.h"
#include <list>
#include "Engine/SpriteResource.h"
#include "State/Playstate.h"
#include "Game/Camera.h"
#include "Item/Coin.h"
#include "Player/Totem.h"

SpriteInfo* EnemyBullet::mspExpInfo;

EnemyBullet::EnemyBullet(std::string id, float x, float y, int angle, int ch_time, float xmod, float ymod, int angle2) :
	Bullet(0, false, false),
	mX(x), mY(y), 
	mAngle(angle),
	mChangeTime(ch_time),
	mModx(xmod), mMody(ymod),
	mAngle2(angle2)
{
	//if angle == -1 use targeting
	if (mAngle < 0)
	{
		mAngle = mAngle + 360;
	}
	mAngle = (mAngle + 10 - 1) / 10 * 10;
	if (mAngle > 360)
		mAngle = 350;
    xvel = sin(mAngle * M_PI/180) * 200; 
    yvel = cos(mAngle * M_PI/180) * 200;
	mClipTimer.Start();
	mExplode = CPlayState::Instance()->mpPlayer->IsBombActive();
	mpRotInfo = &SpriteResource::RequestRotationResource("Attack", id);
	mspExpInfo = &SpriteResource::RequestResource("Attack","enemy_bullet_explode");
	mX = mX - mpRotInfo->width/2;
    mY = mY - mpRotInfo->height/2;
}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::DetectCollision()
{
	if (CPlayState::Instance()->mpPlayer->IsExploding()) 
		return;

    std::list<Totem*>& bounds = CPlayState::Instance()->mpPlayer->GetWpn()->GetTotems();
	for (auto it = bounds.begin(); it != bounds.end(); it++)
		if (IsCollision((*it)->GetBounds()))
		{ 
			(*it)->TakeHit(); 
			return; 
		}
		
	if (IsCollision(CPlayState::Instance()->mpPlayer->GetBounds().rect)) { CPlayState::Instance()->mpPlayer->TakeHit(); return; }
}

bool EnemyBullet::IsCollision(SDL_Rect obj)
{
	float tx = obj.x - mX - Camera::Instance()->CameraX();
	if (tx > TOO_FAR) return false;
	float ty = obj.y - mY - Camera::Instance()->CameraY();
	if (ty > TOO_FAR) return false; 
	float dx = tx + obj.w/2 + mpRotInfo->width/2;
	float dy = ty + obj.h/2 + mpRotInfo->height/2;
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));

	int radii = obj.w/2 + mpRotInfo->width/4;
	if ( ( dx * dx )  + ( dy * dy ) < radii * radii )  {
		mExplode = true;
		return true; }
	else
		return false;
}

void EnemyBullet::Destroy()
{
	//only active bullets when bombed spawn coins
    if (!mExplode)
        CPlayState::Instance()->item_list.push_back(new Coin(mX + mpRotInfo->width/2, mY + mpRotInfo->height/2, 25));
     mExplode = true;
}

void EnemyBullet::CheckBounds()
{
	if( mX + mpRotInfo->width - Camera::Instance()->CameraX() < GAME_BANNER_WIDTH )
	{
		mDelete = true;
	}
	else if( mX - Camera::Instance()->CameraX() > GAME_LEVEL_WIDTH )
	{
		mDelete = true;
	}
	if( mY + mpRotInfo->height - Camera::Instance()->CameraY2() < 0 )
	{
		mDelete = true;
	}
	else if( mY - Camera::Instance()->CameraY2() > GAME_BOUNDS_HEIGHT )
	{
		mDelete = true;
	}
}

void EnemyBullet::Update( const int& rDeltaTime )
{
    if (!mExplode)
    {
		Shared::CheckClip(mClipTimer, mClip, mpRotInfo->interval, mpRotInfo->maxClips,0);
        DetectCollision();
    }
    else
    {
		if (mClip == mspExpInfo->maxClips - 1) mDelete = true;
		Shared::CheckClip(mClipTimer, mClip, mspExpInfo->interval, mspExpInfo->maxClips,0);
	}
	mX += (xvel * ( rDeltaTime / 1000.f ));
	mY += (yvel * ( rDeltaTime / 1000.f ));

    CheckBounds();
}

void EnemyBullet::Draw(SDL_Surface* pDest)
{ 
    if (!mExplode)
    {
        Camera::Instance()->DrawSurface(mX - mpRotInfo->width/2, mY - mpRotInfo->height/2,
			mpRotInfo->pSurface[mClip][mAngle], pDest, NULL);
    }
    else
    {
        Camera::Instance()->DrawSurface(mX + (mpRotInfo->width/4 - mspExpInfo->width/4), mY + (mpRotInfo->height/4 - mspExpInfo->height/4), 
			mspExpInfo->pSurface, pDest, &mspExpInfo->pClips[mClip]);
    }
}