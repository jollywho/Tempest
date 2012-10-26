#include "BulletM.h"
#include "State/playstate.h"
#include "Engine/SpriteResource.h"
#include "Player/Player.h"
#include "Game/Camera.h"

RotationInfo* BulletM::_info;
SpriteInfo* BulletM::_expInfo;

BulletM::BulletM(float x, float y, int angl, int rots) :
	PlayerBullet(x, y, angl, rots)
{
	offset.w = _info->width;
    offset.h = _info->height;
    xVal = x - _info->width/2 + Camera::CameraX();
    yVal = y - _info->height/2 + Camera::CameraY2();
    offset.x = xVal;
    offset.y = yVal;
}

void BulletM::Init(std::string id, std::string expId)
{
	_info = &SpriteResource::RequestRotationResource("Player",id);
	_expInfo = &SpriteResource::RequestResource("Player", expId);
	min_bounds.x = _G_BANNER_WIDTH;
	min_bounds.y = 0;
	max_bounds.x = _G_BOUNDS_WIDTH;
	max_bounds.y = _G_BOUNDS_HEIGHT;
}

void BulletM::Update(const int& iElapsedTime)
{
    if (!exploding)
    {
		Shared::CheckClip(clip_timer, clip, _info->interval, _info->clip_count,0);
		yVal += (yVel * ( iElapsedTime / 1000.f ));
		xVal += (xVel * ( iElapsedTime / 1000.f ));
		//CheckCollision(_expInfo->width, _expInfo->height);
		CheckBounds(Point(Camera::CameraX(), Camera::CameraY2()));
    }
    else
    {
		offset.x = offset.x + (offset.w/2 - _expInfo->width/2);
        offset.y = offset.y + (offset.h/2 - _expInfo->height/2);
		if (clip >= _expInfo->clip_count - 1) m_delete = true;
		Shared::CheckClip(clip_timer, clip, _expInfo->interval, _expInfo->clip_count, 0);
	}
	offset.x = xVal;
	offset.y = yVal;
}

void BulletM::Draw(SDL_Surface *dest)
{ 
    if (!exploding)
    {
        Camera::DrawSurface(offset.x - offset.w/2, offset.y-offset.h/2, _info->rot_surface[0][angle], dest, NULL);
    }
    else
    {
        Shared::apply_surface(offset.x + (offset.w/4 - _expInfo->width/4), offset.y + (offset.h/4 - _expInfo->height/4), 
			_expInfo->surface, dest, &_expInfo->clips[clip]);
    }
}