#include "PlayerBullet.h"
#include "State/playstate.h"
#include "Engine/SpriteResource.h"
//#include "Enemy.h"
//#include "Player.h"

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
    xVel = sin(angle * M_PI/180) * 1600; 
    yVel = cos(angle * M_PI/180) * 1600;
	
    clip_timer.start();
}

void PlayerBullet::CheckCollision(int expW, int expH)
{
	/* todo: link enemy list
    for (auto it = CPlayState::Instance()->enemyList.begin(); it != CPlayState::Instance()->enemyList.end();)
    {
		if ((*it)->active && !(*it)->exploding)
		{
        SDL_Rect enemybounds = (*it)->GetBounds();

        if (enemybounds.x+enemybounds.w>offset.x  && 
            enemybounds.x<offset.x+offset.w  && 
            enemybounds.y+enemybounds.h>offset.y && 
            enemybounds.y<offset.y+offset.h)
            { 
                (*it)->TakeHit(1);
                frame_Timer.start();
                exploding = true;
                offset.x = offset.x + (offset.w/2 - expW/2);
                offset.y = offset.y + (offset.h/2 - expH/2);
                break;
			}
		}
        it++;
    }
	*/
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
	else if( offset.y - offset.h - camera_pos.y > max_bounds.y )
	{
		m_delete = true;
	}
}