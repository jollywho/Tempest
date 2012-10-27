#include "Pollstate.h"
#include "Engine/Shared.h"
#include "UI/Menu.h"
#include "Sprig.h"
#include "Engine/SpriteResource.h"
#include "UI/Decor.h"

CPollState CPollState::m_IntroState;

void CPollState::Init()
{
	printf("CPollState Init\n");
	ClearRequest();
	bg =  Shared::load_image("Image/UI/poll.bmp");

	banner_middle = Shared::load_image("Image/UI/poll_banner_side.png");
	banner_side = Shared::load_image("Image/UI/poll_banner_middle.png");

	//todo: nsprites

	//todo: load scores

	alpha = 255;
	//

	banner_middle_pos.x = _WSCREEN_WIDTH/2 - 112/2;
	banner_middle_pos.y = _WSCREEN_HEIGHT;

	banner_left_pos.x = _G_BANNER_WIDTH - 116;
	banner_left_pos.y = _WSCREEN_HEIGHT/2 - 412/2;

	banner_right_pos.x = _G_BOUNDS_WIDTH;
	banner_right_pos.y = _WSCREEN_HEIGHT/2 - 412/2;

	exiting = false; entering = true; fadeout = false;

	fade_timer.start();
}

void CPollState::Cleanup()
{
	printf("CPollState Cleanup\n");
	SDL_FreeSurface(bg);

	SDL_FreeSurface(banner_middle);
	SDL_FreeSurface(banner_side);
}

void CPollState::Pause()
{
	printf("CPollState Pause\n");
}

void CPollState::Resume()
{
	printf("CPollState Resume\n");
}

void CPollState::CheckKeys(const KeyStruct& keys)
{
	if (exiting) return;
	if (keys.z)
	{
		//todo: skip
		//todo: if skip | ready => change state
	}
}

void CPollState::Update(const int& iElapsedTime) 
{
	if (entering)
	{
		if (alpha >= 2) 
		{
			if (fade_timer.get_ticks() > 10) 
			{
				alpha-=2;
				fade_timer.start(); 
			} 
		}
		else if (banner_middle_pos.y < 0)
		{
			banner_middle_pos.y+=2;
		}
		else if (banner_left_pos.x < banner_middle_pos.x)
		{
			banner_left_pos.x+=2;
			banner_right_pos.x-=2;
		}
		else
			entering = false;
	}
	else if (exiting)
	{
		if (alpha < 255) 
		{
			if (fade_timer.get_ticks() > 10) 
			{
				alpha+=2;
				fade_timer.start(); 
			} 
		}
		else
			RequestState(Play);
	}

	/*
	todo: ELSE {}
	1) Show Nsprite/ Update
	2) Count its coins until done
	3) Next item
	4) If item count = 3, ready = true

	*/
}

void CPollState::Draw(SDL_Surface* dest) 
{
	Shared::apply_surface(0,0,bg,dest);

	Shared::apply_surface(banner_left_pos.x, banner_left_pos.y, banner_side, dest);
	Shared::apply_surface(banner_right_pos.x, banner_right_pos.y, banner_side, dest);
	Shared::apply_surface(banner_middle_pos.x, banner_middle_pos.y, banner_middle, dest);

	//todo: draw game/ui
	//todo: draw nsprite

	SPG_RectFilledBlend(dest,0,0,_WSCREEN_WIDTH,_WSCREEN_HEIGHT, 0, alpha);
}
