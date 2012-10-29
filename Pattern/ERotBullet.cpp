#include "ERotBullet.h"
#include "Engine/SpriteResource.h"
#include "Game/Camera.h"

ERotBullet::ERotBullet(float x, float y, int angle, std::string id) : EnemyBullet()
{
	mAngle = angle;
	if (mAngle < 0)
	{
		mAngle = mAngle + 360;
	}
	mAngle = (mAngle + 10 - 1) / 10 * 10;
	if (mAngle > 360)
		mAngle = 350;
    xvel = sin(mAngle * M_PI/180) * 200; 
    yvel = cos(mAngle * M_PI/180) * 200;
    
	mpRotInfo = &SpriteResource::RequestRotationResource("Attacks", id);
    mX = x - mpRotInfo->width/2;
    mY = y - mpRotInfo->height/2;
}

void ERotBullet::Update( const int& rDeltaTime )
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

void ERotBullet::Draw(SDL_Surface* pDest)
{ 
    if (!mExplode)
    {
        Camera::DrawSurface(mX - mpRotInfo->width/2, mY - mpRotInfo->height/2,
			mpRotInfo->pSurface[mClip][mAngle], pDest, NULL);
    }
    else
    {
        Camera::DrawSurface(mX + (mpRotInfo->width/4 - mspExpInfo->width/4), mY + (mpRotInfo->height/4 - mspExpInfo->height/4), 
			mspExpInfo->pSurface, pDest, &mspExpInfo->pClips[mClip]);
    }
}