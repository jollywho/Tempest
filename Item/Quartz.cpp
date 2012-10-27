#include "Quartz.h"
#include "Engine/SpriteResource.h"
#include "Game/Interface.h"
#include "Game/Gamescore.h"
#include "Game/Camera.h"
#include "State/playstate.h"
#include "Player/Player.h"
#include "UI/ScoreMSG.h"

Quartz::Quartz(int x, int y, int value) : Item(x, y, 1000, "Quartz.png")
{
	Air = false;
    m_delete = false;
	lockedOn = false;
	clip = 0;
}

Quartz::~Quartz() 
{
	if (pickedup)
	{
		GameScore::Instance()->IncreaseQuartzCount();
		CPlayState::Instance()->score_list.push_back(new ScoreMSG(xVal, yVal - Camera::CameraY2(), spawnside, GameScore::Instance()->GetBonus() * val));
	}
}

void Quartz::Update(Uint32 deltaTicks)
{
	if (pickedup) m_delete = true;
	Shared::CheckClip(clip_Timer, clip, 50, _info->clip_count, 0);
	SDL_Rect playerbox = CPlayState::Instance()->player->GetOuterBounds();
    float dx = (playerbox.x + playerbox.w/2) - (offset.x - Camera::CameraX()  + offset.w/2);
    float dy = (playerbox.y + playerbox.h/2) - (offset.y - Camera::CameraY2() + offset.h/2);
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));

	if (Length > 0.1f && Length < 100 && duration_Timer.get_ticks() > 600 && !lockedOn)
	{
		lockedOn = true;
		accel_Timer.start();
	}

	if (lockedOn)
	{
		float xa = dx / Length;
		float ya = dy / Length;
		yVel+=accel_Timer.get_ticks()/50;
		xVal += (xa * (yVel * (deltaTicks / 1000.f)));
		yVal += (ya * (yVel * (deltaTicks / 1000.f)));
		Check_Collision();
	}
	else
	{
		yVal += (yVel * (deltaTicks / 1000.f));
	}
	offset.x = xVal;
    offset.y = yVal;

    
	if (CheckOffscreen(xVal, yVal - Camera::CameraY2(), _info->height))
		m_delete = true;
}

void Quartz::Draw(SDL_Surface *dest)
{
    Camera::DrawSurface(offset.x, offset.y,
        _info->surface, dest, &_info->clips[clip]);
}