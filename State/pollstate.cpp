#include "Pollstate.h"
#include "Engine/Shared.h"
#include "Game/Interface.h"
#include "Sprig.h"
#include "Engine/SpriteResource.h"
#include "playstate.h"

CPollState CPollState::mIntroState;

void CPollState::Init()
{
	printf("CPollState initialize\n");
	ClearRequest();
	mpBackground =  Shared::LoadImage("Image/UI/poll.bmp");

	banner_middle = Shared::LoadImage("Image/UI/poll_banner_middle.png");
	banner_side = Shared::LoadImage("Image/UI/poll_banner_side.png");

	//todo: nsprites

	//todo: load scores

	mAlpha = 255;
	banner_speed = 12;
	//

	banner_middle_pos.x = WINDOW_WIDTH/2 - 112/2;
	banner_middle_pos.y = WINDOW_HEIGHT;

	banner_left_pos.x = GAME_BANNER_WIDTH - 116;
	banner_left_pos.y = WINDOW_HEIGHT/2 - 412/2;

	banner_right_pos.x = GAME_BOUNDS_WIDTH;
	banner_right_pos.y = WINDOW_HEIGHT/2 - 412/2;

	mExit = false; mEnter = true; mFadeout = false;

	mFadeTimer.Start();
}

void CPollState::Cleanup()
{
	printf("CPollState Cleanup\n");
	SDL_FreeSurface(mpBackground);

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

void CPollState::KeyInput(const KeyStruct& rKeys)
{
	if (mExit) return;
	if (rKeys.z)
	{
		mExit = true;
		//todo: skip
		//todo: if skip | ready => change state
	}
}

void CPollState::Update(const int& rDeltaTime) 
{
	if (mEnter)
	{
		if (mAlpha > 0) 
		{
			if (mFadeTimer.GetTicks() > 10) 
			{
				mAlpha-=5;
				mFadeTimer.Start(); 
			} 
		}
		if (banner_middle_pos.y > 50)
		{
			banner_middle_pos.y-=banner_speed;
		}
		if (banner_left_pos.x < banner_middle_pos.x - 102) //offset to overlap
		{
			banner_left_pos.x+=banner_speed/4;
			banner_right_pos.x-=banner_speed/4;
		}
		else
			if (mAlpha <= 2 )
				mEnter = false;
			
	}
	else if (mExit)
	{		
		if (mAlpha < 255) 
		{
			if (mFadeTimer.GetTicks() > 10) 
			{
				mAlpha+=5;
				mFadeTimer.Start(); 
			} 
		}
		else
			PopState();
	}

	CPlayState::Instance()->mpInterface->Update(rDeltaTime);

	/*
	todo: ELSE {}
	1) Show Nsprite/ Update
	2) Count its coins until done
	3) Next item
	4) If item count = 3, ready = true

	*/
}

void CPollState::Draw(SDL_Surface* pDest) 
{
	Shared::DrawSurface(0, 0, mpBackground, pDest);

	Shared::DrawSurface(banner_left_pos.x, banner_left_pos.y, banner_side, pDest);
	Shared::DrawSurface(banner_right_pos.x, banner_right_pos.y, banner_side, pDest);
	Shared::DrawSurface(banner_middle_pos.x, banner_middle_pos.y, banner_middle, pDest);

	//todo: draw nsprite

	//fadeout area based on sub state
	SPG_RectFilledBlend(pDest, GAME_BANNER_WIDTH, 0, GAME_BOUNDS_WIDTH, WINDOW_HEIGHT, 16777215, mAlpha);

	CPlayState::Instance()->mpInterface->Draw(pDest);
	//todo: draw game/ui
}
