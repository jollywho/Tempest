#include "BulletM.h"
#include "State/playstate.h"
#include "Engine/SpriteResource.h"
#include "Player/Player.h"
#include "Game/Camera.h"

RotationInfo* BulletM::mpInfo;
SpriteInfo* BulletM::_expInfo;

BulletM::BulletM(float x, float y, int angl, int rots) :
	PlayerBullet(x, y, angl, rots)
{
	mOffset.w = mpInfo->width;
    mOffset.h = mpInfo->height;
    mX = x - mpInfo->width/2 + Camera::CameraX();
    mY = y - mpInfo->height/2 + Camera::CameraY2();
    mOffset.x = mX;
    mOffset.y = mY;
}

void BulletM::Init(std::string id, std::string expId)
{
	mpInfo = &SpriteResource::RequestRotationResource("Player",id);
	_expInfo = &SpriteResource::RequestResource("Player", expId);
	min_bounds.x = GAME_BANNER_WIDTH;
	min_bounds.y = 0;
	max_bounds.x = GAME_BOUNDS_WIDTH;
	max_bounds.y = GAME_BOUNDS_HEIGHT;
}

void BulletM::Update(const int& rDeltaTime)
{
    if (!mExplode)
    {
		Shared::CheckClip(mClipTimer, mClip, mpInfo->interval, mpInfo->maxClips,0);
		mY += (yvel * ( rDeltaTime / 1000.f ));
		mX += (xvel * ( rDeltaTime / 1000.f ));
		CheckBounds(Point(Camera::CameraX(), Camera::CameraY2()));
    }
    else
    {
		mOffset.x = mOffset.x + (mOffset.w/2 - _expInfo->width/2);
        mOffset.y = mOffset.y + (mOffset.h/2 - _expInfo->height/2);
		if (mClip >= _expInfo->maxClips - 1) mDelete = true;
		Shared::CheckClip(mClipTimer, mClip, _expInfo->interval, _expInfo->maxClips, 0);
	}
	mOffset.x = mX;
	mOffset.y = mY;
}

void BulletM::Draw(SDL_Surface *pDest)
{ 
    if (!mExplode)
    {
        Camera::DrawSurface(mOffset.x - mOffset.w/2, mOffset.y-mOffset.h/2, mpInfo->pSurface[0][mAngle], pDest, NULL);
    }
    else
    {
        Camera::DrawSurface(mOffset.x + (mOffset.w/4 - _expInfo->width/4), mOffset.y + (mOffset.h/4 - _expInfo->height/4), 
			_expInfo->pSurface, pDest, &_expInfo->pClips[mClip]);
    }
}