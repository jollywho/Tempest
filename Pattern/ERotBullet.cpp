#include "ERotBullet.h"
#include "Engine/SpriteResource.h"
#include "Game/Camera.h"

ERotBullet::ERotBullet(float x, float y, int angl, std::string id) : EnemyBullet()
{
	angle = angl;
	if (angle < 0)
	{
		angle = angle + 360;
	}
	angle = (angle + 10 - 1) / 10 * 10;
	if (angle >= 360)
		angle = 350;
    xVel = sin(angle * M_PI/180) * 100; 
    yVel = cos(angle * M_PI/180) * 100;
    clip_timer.start();
	info = &SpriteResource::RequestRotationResource("Attacks",id);
    xVal = x - info->width/2;
    yVal = y - info->height/2;
}

void ERotBullet::Update( Uint32 deltaTicks )
{
    if (!exploding)
    {
		Shared::CheckClip(clip_timer, clip, info->interval, info->clip_count,0);
        DetectCollision();
    }
    else
    {
		if (clip == expinfo->clip_count - 1) m_delete = true;
		Shared::CheckClip(clip_timer, clip, expinfo->interval, expinfo->clip_count,0);
	}
	yVal += (yVel * ( deltaTicks / 1000.f ));
    xVal += (xVel * ( deltaTicks / 1000.f ));

    CheckBounds();
}

void ERotBullet::Draw(SDL_Surface *dest)
{ 
    if (!exploding)
    {
        Camera::DrawSurface(xVal - info->width/2, yVal - info->height/2,
		info->rot_surface[clip][angle], dest, NULL);
    }
    else
    {
        Camera::DrawSurface(xVal + (info->width/4 - expinfo->width/4), xVal + (info->height/4 - expinfo->height/4), 
		expinfo->surface, dest, &expinfo->clips[clip]);
    }
}