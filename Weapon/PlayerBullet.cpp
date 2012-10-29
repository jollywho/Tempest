#include "PlayerBullet.h"
#include "State/playstate.h"
#include "Engine/SpriteResource.h"
#include "Enemy/Enemy.h"

Point PlayerBullet::min_bounds;
Point PlayerBullet::max_bounds;

PlayerBullet::PlayerBullet(float x, float y, int angl, int rots)
{
    mDelete = false;
    mExplode = false;
	mClip = 0;

	mAngle = -angl;
	if (mAngle < 0)
	{
		mAngle = mAngle + 360;
	}
	mAngle = (mAngle + rots - 1) / rots * rots;
	if (mAngle > 360)
		mAngle = 360;
    xvel = sinf(mAngle * (float)(M_PI/180)) * 1600; 
    yvel = cosf(mAngle * (float)(M_PI/180)) * 1600;
	
    mClipTimer.Start();
}

void PlayerBullet::DetectCollision()
{
	if (mExplode) return;
    for (auto it = CPlayState::Instance()->enemy_list.begin(); it != CPlayState::Instance()->enemy_list.end(); it++)
    {
		if (!(*it)->IsExploding())
		{
			SDL_Rect enemybounds = (*it)->GetBounds();

			int dx = (enemybounds.x + enemybounds.w/2) - (mOffset.x  + mOffset.w/2);
			int dy = (enemybounds.y + enemybounds.h/2) - (mOffset.y  + mOffset.h/2);

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

void PlayerBullet::CheckBounds(Point camera_pos)
{
	if( mOffset.x + mOffset.w - camera_pos.x < min_bounds.x - mOffset.w )
	{
		mDelete = true;
	}
	else if( mOffset.x - camera_pos.x > max_bounds.x )
	{
		mDelete = true;
	}
	if( mOffset.y + mOffset.h - camera_pos.y < 0 + min_bounds.y )
	{
		mDelete = true;
	}
	else if( mOffset.y - camera_pos.y > max_bounds.y )
	{
		mDelete = true;
	}
}