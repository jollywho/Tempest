#include "EnemyBullet.h"
#include "Engine/SpriteResource.h"
#include "State/Playstate.h"
#include "Game/Camera.h"
#include "Item/Coin.h"

SpriteInfo* EnemyBullet::mspExpInfo;

EnemyBullet::EnemyBullet()
{
	mClip = 0;
	mClipTimer.Start();
	mDelete = false;
	mExplode = CPlayState::Instance()->mpPlayer->IsBombActive();
}

void EnemyBullet::Init()
{
	SpriteResource::AddResource("Attacks","enemy_bullet_explode.png", 32,32,80,8);
	SpriteResource::AddResource("Attacks","LargeRed.png", 28,28,80,3);
	SpriteResource::AddRotationResource("Attacks","Arrow.png",28,28,80,4,0,360,28,28,14,14);
	mspExpInfo = &SpriteResource::RequestResource("Attacks","enemy_bullet_explode.png");
}

void EnemyBullet::DetectCollision()
{
	if (CPlayState::Instance()->mpPlayer->IsExploding()) 
		return;

    SDL_Rect playerbox = CPlayState::Instance()->mpPlayer->GetBounds().rect;
    float dx = (playerbox.x + playerbox.w/2) - (mX - Camera::Instance()->CameraX()  + mpRotInfo->width/2);
    float dy = (playerbox.y + playerbox.h/2) - (mY - Camera::Instance()->CameraY2() + mpRotInfo->height/2);
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));

    int radii = playerbox.w/2 + mpRotInfo->width/4;
    if ( ( dx * dx )  + ( dy * dy ) < radii * radii ) 
    {
        mExplode = true;
        CPlayState::Instance()->mpPlayer->TakeHit();
    }
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