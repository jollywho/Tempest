/* Tempest - C++ Danmakufu Game for SDL
*
*  Copyright (C) 2013 Kevin Vollmer.
*  
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*  
ÅÅ*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
#include "PlayerBullet.h"
#include "State/playstate.h"
#include "Engine/SpriteResource.h"
#include "Enemy/Enemy.h"
#include "Game/Camera.h"

RotationInfo* PlayerBullet::mpInfo;
SpriteInfo* PlayerBullet::_expInfo;
Point PlayerBullet::msMinBounds;
Point PlayerBullet::msMaxBounds;

PlayerBullet::PlayerBullet(float x, float y, int angle, int rots) :
	Bullet(0, false, false),
	mX(x), mY(y),
	mAngle(-angle),
	mRots(rots),
	mOffset(),
	xvel(0), yvel(0)
{
	if (mAngle < 0)
	{
		mAngle = mAngle + 360;
	}
	mAngle = (mAngle + rots - 1) / rots * rots;
	if (mAngle > 360)
		mAngle = 360;
    xvel = sinf(mAngle * (float)(M_PI/180)) * 1600; 
    yvel = cosf(mAngle * (float)(M_PI/180)) * 1600;
	
	mOffset.w = mpInfo->width;
    mOffset.h = mpInfo->height;
    mX = x - mpInfo->width/2 + Camera::Instance()->Instance()->CameraX();
    mY = y - mpInfo->height/2 + Camera::Instance()->Instance()->CameraY2();
	mOffset.x = mX;
    mOffset.y = mY;
    mClipTimer.Start();
}

void PlayerBullet::Init(std::string id, std::string expId)
{
    mpInfo = &SpriteResource::RequestRotationResource("Player",id);
    _expInfo = &SpriteResource::RequestResource("Player", expId);
    msMinBounds.x = GAME_BANNER_WIDTH;
    msMinBounds.y = 0;
    msMaxBounds.x = GAME_BOUNDS_WIDTH;
    msMaxBounds.y = GAME_BOUNDS_HEIGHT;
}

void PlayerBullet::DetectCollision()
{
	if (mExplode) return;
    for (auto it = CPlayState::Instance()->enemy_list.begin(); it != CPlayState::Instance()->enemy_list.end(); it++)
    {
		if (!(*it)->IsExploding())
		{
			SDL_Rect enemybounds = (*it)->GetBounds();
			
			int dx = enemybounds.x + enemybounds.w/2 - mOffset.x + mOffset.w/2;
			if (dx < 50) 
			{
				int dy = enemybounds.y + enemybounds.h/2 - mOffset.y + mOffset.h/2;
				if (dy < 50)
				{
					int radii = enemybounds.w/2 + mOffset.w/4;
					if ( ( dx * dx )  + ( dy * dy ) < radii * radii ) 
					{
						(*it)->TakeHit(1);
						mClip = 0;
						mClipTimer.Start();
						mExplode = true;
						return;
					}
				}
			}
		}
    }
}

void PlayerBullet::CheckBounds(Point camera_pos)
{
	//all player bullets are north directional and only need one bounds check
	if( mOffset.y + mOffset.h - camera_pos.y < 0)
		mDelete = true;
}
void PlayerBullet::Update(const int& rDeltaTime)
{
    if (!mExplode)
    {
		Shared::CheckClip(mClipTimer, mClip, mpInfo->interval, mpInfo->maxClips,0);
		mY += (yvel * ( rDeltaTime / 1000.f ));
		mX += (xvel * ( rDeltaTime / 1000.f ));
		CheckBounds(Point(Camera::Instance()->Instance()->Camera::Instance()->CameraX(), Camera::Instance()->Instance()->CameraY2()));
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

void PlayerBullet::Draw(SDL_Surface *pdest)
{ 
    if (!mExplode)
    {
        Camera::Instance()->Instance()->DrawSurface(mOffset.x - mOffset.w/2, mOffset.y-mOffset.h/2, mpInfo->pSurface[0][mAngle], pdest, NULL);
    }
    else
    {
        Camera::Instance()->Instance()->DrawSurface(mOffset.x + (mOffset.w/4 - _expInfo->width/4), mOffset.y + (mOffset.h/4 - _expInfo->height/4), 
			_expInfo->pSurface, pdest, &_expInfo->pClips[mClip]);
    }
}