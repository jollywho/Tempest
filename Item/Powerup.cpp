#include "Powerup.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "Game/Interface.h"
#include "Game/Camera.h"
#include "Player/Player.h"
#include "Game/GameScore.h"

Powerup::Powerup(int x, int y, int value) : Item(x, y, value, "Powerup.png")
{
	Air = true;
	_received = &SpriteResource::RequestResource("Items", "Powerup_Received.png");
    m_delete = false;
	yVel = 200 * ((rand() % 2) == 1 ? -1 : 1);
	xVel = 200 * ((rand() % 2) == 1 ? -1 : 1);
}

Powerup::~Powerup() 
{

}

void Powerup::Update(Uint32 deltaTicks)
{
	if (pickedup)
	{
		Shared::CheckClip(clip_Timer, clip, _received->interval, _received->clip_count, 0);
		if (!received) 
		{
			SFX::PlaySoundResource("powerup_pickup.wav");
			received = true;
			duration_Timer.start(); 
			CPlayState::Instance()->player->WeaponLevelUp();
			yVel = -100;
			xVel = 0;
		}
		if (duration_Timer.get_ticks() > 1000)
			m_delete = true;
	}
	else 
	{
		Shared::CheckClip(clip_Timer, clip, 50, _info->clip_count, 0);
		Check_Collision();
		Check_WallCollision(_info->width, _info->height);
	}
	
	xVal += (xVel * (deltaTicks / 1000.f));
	yVal += (yVel * (deltaTicks / 1000.f));

	offset.x = xVal;
    offset.y = yVal;
}

void Powerup::Draw(SDL_Surface *dest)
{
	if (pickedup) {
		Camera::DrawSurface(offset.x - 40, offset.y + Camera::CameraY2() - 25,
			received_frame, dest, NULL);
		Camera::DrawSurface(offset.x, offset.y + Camera::CameraY2(),
			_received->surface, dest, &_received->clips[clip]);
	}
	else
		Camera::DrawSurface(offset.x, offset.y + Camera::CameraY2(),
			_info->surface, dest, &_info->clips[clip]);
}