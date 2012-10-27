#include "EnemyBullet.h"
#include "Engine/SpriteResource.h"
#include "State/Playstate.h"
#include "Game/Camera.h"

SpriteInfo* EnemyBullet::expinfo;

EnemyBullet::EnemyBullet()
{
	clip = 0;
	clip_timer.start();
	m_delete = false;

	exploding = CPlayState::Instance()->player->IsBombActive();
}

void EnemyBullet::Init()
{
	SpriteResource::AddResource("Attacks","enemy_bullet_explode.png", 32,32,80,8);
	SpriteResource::AddResource("Attacks","LargeRed.png", 28,28,80,3);
	SpriteResource::AddRotationResource("Attacks","Arrow.png",28,28,80,4,0,360,28,28,14,14);
	expinfo = &SpriteResource::RequestResource("Attacks","enemy_bullet_explode.png");
}

void EnemyBullet::DetectCollision()
{
	//todo: player->IsInvuln/Exploding
    SDL_Rect playerbox = CPlayState::Instance()->player->GetBounds();
    float dx = (playerbox.x + playerbox.w/2) - (xVal - Camera::CameraX()  + info->width/2);
    float dy = (playerbox.y + playerbox.h/2) - (yVal - Camera::CameraY2() + info->height/2);
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