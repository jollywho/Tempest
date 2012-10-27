#include "Bomb.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "Game/GameScore.h"
#include "Game/Camera.h"
#include "Player/Player.h"

Bomb::Bomb(int x, int y, int value) : Item(x, y, value, "Bomb.png")
{
	_received = &SpriteResource::RequestResource("Items", "Bomb_Received.png");
	Air = true;
    m_delete = false;
	yVel = 200 * ((rand() % 2) == 1 ? -1 : 1);
	xVel = 200 * ((rand() % 2) == 1 ? -1 : 1);
}

Bomb::~Bomb() 
{
}

void Bomb::Update(Uint32 deltaTicks)
{
	if (pickedup)
	{
		Shared::CheckClip(clip_Timer, clip, _received->interval, _received->clip_count, _received->clip_count-1);
		if (!received) 
		{
			SFX::PlaySoundResource("bomb_pickup.wav");
			received = true;
			duration_Timer.start(); 
			GameScore::Instance()->IncreaseBombs();
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

void Bomb::Draw(SDL_Surface *dest)
{
	if (pickedup) {
		Camera::DrawSurface(offset.x - 50, offset.y + Camera::CameraY2() - 25,
			received_frame, dest, NULL);
		Camera::DrawSurface(offset.x, offset.y + Camera::CameraY2(),
			_received->surface, dest, &_received->clips[clip]);
	}
	else
		Camera::DrawSurface(offset.x, offset.y + Camera::CameraY2(),
			_info->surface, dest, &_info->clips[clip]);
}