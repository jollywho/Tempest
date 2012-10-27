#include "EnemyBullet.h"
#include "Engine/SpriteResource.h"
#include "State/Playstate.h"
#include "Game/Camera.h"

SpriteInfo* EnemyBullet::expinfo;

void EnemyBullet::Init()
{
	//exp info add and request
}

void EnemyBullet::DetectCollision()
{
    SDL_Rect playerbox = CPlayState::Instance()->player->GetBounds();
    float dx = (playerbox.x + playerbox.w/2) - (xVal - Camera::CameraX()  + info->width/2);
    float dy = (playerbox.y + playerbox.h/2) - (yVal + info->height/2);
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));

    int radii = playerbox.w/2 + info->width/4;
    if ( ( dx * dx )  + ( dy * dy ) < radii * radii ) 
    {
        exploding = true;
        CPlayState::Instance()->player->TakeHit();
    }
}

void EnemyBullet::Destroy()
{
    if (!exploding)
        bombed = true;
     exploding = true;
}

void EnemyBullet::CheckBounds()
{
	if( xVal + info->width - Camera::CameraX() < _G_BANNER_WIDTH )
	{
		m_delete = true;
	}
	else if( xVal - Camera::CameraX() > _G_LEVEL_WIDTH )
	{
		m_delete = true;
	}
	if( yVal + info->height - Camera::CameraY2() < 0 )
	{
		m_delete = true;
	}
	else if( yVal - Camera::CameraY2() > _G_BOUNDS_HEIGHT )
	{
		m_delete = true;
	}
}