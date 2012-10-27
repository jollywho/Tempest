#include "Gem.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "Game/Interface.h"
#include "Game/Camera.h"
#include "Player/Player.h"
#include "Game/GameScore.h"
#include "UI/ScoreMsg.h"

Gem::Gem(int x, int y, int value, bool autolock) : Item(x, y, value, "Gem.png")
{
	Air = true;
    m_delete = false;
	yVel = -200;
	lockedOn = autolock;
	clip = 0;
	accel_Timer.start();
}

Gem::~Gem() 
{
	if (pickedup)
	{
		GameScore::Instance()->IncreaseGemCount();
		GameScore::Instance()->IncreaseBonus();
		SFX::PlaySoundResource("gem_pickup.wav");
		//CPlayState::Instance()->scoreMsgList.push_back(new ScoreMSG(xVal, yVal, spawnside, GameScore::Instance()->GetBonus() * val));
		CPlayState::Instance()->score_list.push_back(new ScoreMSG(xVal, yVal, spawnside, val));
	}
}

void Gem::Update(Uint32 deltaTicks)
{
	if (pickedup) m_delete = true;
	Shared::CheckClip(clip_Timer, clip, 50, _info->clip_count, 0);

	SDL_Rect playerbox = CPlayState::Instance()->player->GetOuterBounds();
    float dx = (playerbox.x + playerbox.w/2) - (offset.x - Camera::CameraX()  + offset.w/2);
    float dy = (playerbox.y + playerbox.h/2) - (offset.y + offset.h/2);
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));

	if (Length > 0.1f && Length < 200 && !lockedOn)
	{
		lockedOn = true;
		accel_Timer.start();
	}

	if (CPlayState::Instance()->player->IsExploding() )
		lockedOn = false;

	if ((lockedOn) && duration_Timer.get_ticks() > 600)
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
		if (duration_Timer.get_ticks() > 200) yVel+= 500 * deltaTicks/1000.f;
		yVal += (yVel * (deltaTicks / 1000.f));
	}
	offset.x = xVal;
    offset.y = yVal;

    
	if (CheckOffscreen(xVal, yVal, _info->height))
		m_delete = true;
}

void Gem::Draw(SDL_Surface *dest)
{
    Camera::DrawSurface(offset.x, offset.y + Camera::CameraY2(),
        _info->surface, dest, &_info->clips[clip]);
}