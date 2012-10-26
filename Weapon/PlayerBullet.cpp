#include "PlayerBullet.h"
#include "State/playstate.h"
#include "Engine/SpriteResource.h"
#include "Enemy/Enemy.h"

Point PlayerBullet::min_bounds;
Point PlayerBullet::max_bounds;

PlayerBullet::PlayerBullet(float x, float y, int angl, int rots)
{
    m_delete = false;
    exploding = false;
	clip = 0;

	angle = -angl;
	if (angle < 0)
	{
		angle = angle + 360;
	}
	angle = (angle + rots - 1) / rots * rots;
	if (angle > 360)
		angle = 360;
    xVel = sinf(angle * (float)(M_PI/180)) * 1600; 
    yVel = cosf(angle * (float)(M_PI/180)) * 1600;
	
    clip_timer.start();
}

void PlayerBullet::CheckCollision()
{
    for (auto it = CPlayState::Instance()->enemy_list.begin(); it != CPlayState::Instance()->enemy_list.end(); it++)
    {
		if (!(*it)->IsExploding())
		{
			SDL_Rect enemybounds = (*it)->GetBounds();

			int dx = (enemybounds.x + enemybounds.w/2) - (offset.x  + offset.w/2);
			int dy = (enemybounds.y + enemybounds.h/2) - (offset.y  + offset.h/2);

			int radii = enemybounds.w/2 + offset.w/4;
			if ( ( dx * dx )  + ( dy * dy ) < radii * radii ) 
			{
					(*it)->TakeHit(1);
					clip_timer.start();
					exploding = true;
					return;
			}
		}
    }
}

void PlayerBullet::CheckBounds(Point camera_pos)
{
	if( offset.x + offset.w - camera_pos.x < min_bounds.x - offset.w )
	{
		m_delete = true;
	}
	else if( offset.x - camera_pos.x > max_bounds.x )
	{
		m_delete = true;
	}
	if( offset.y + offset.h - camera_pos.y < 0 + min_bounds.y )
	{
		m_delete = true;
	}
	else if( offset.y - camera_pos.y > max_bounds.y )
	{
		m_delete = true;
	}
}