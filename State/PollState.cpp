/* Tempest - C++ Danmakufu Game for SDL
*
*  Copyright (C) 2013 Kevin Vollmer.
*  
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*  
ÅÅ*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
#include "PollState.h"
#include "Engine/Shared.h"
#include "Engine/FontResource.h"
#include "Engine/SpriteResource.h"
#include "Game/Gamescore.h"
#include "UI/NSprite.h"
#include "UI/Interface.h"
#include "Sprig.h"
#include "PlayState.h"

CPollState CPollState::mIntroState;

void CPollState::Init()
{
	printf("CPollState initialize\n");
	ClearRequest();
	mpBackground =  Shared::LoadImage("Image/UI/poll.bmp");
	banner_middle = Shared::LoadImage("Image/UI/poll_banner_middle.png");
	banner_side = Shared::LoadImage("Image/UI/poll_banner_side.png");
	mpFont = &FontResource::RequestFont("bobble_red");

	/* Banners */
	banner_middle_pos.x = WINDOW_WIDTH/2 - 112/2;
	banner_middle_pos.y = WINDOW_HEIGHT;
	banner_left_pos.x = GAME_BANNER_WIDTH - 116;
	banner_left_pos.y = WINDOW_HEIGHT/2 - 412/2;
	banner_right_pos.x = GAME_BOUNDS_WIDTH;
	banner_right_pos.y = WINDOW_HEIGHT/2 - 412/2;
	mAlpha = 255;
	banner_speed = 12;

	/* Items */
	Reset(mGem);
	Reset(mCoin);
	Reset(mQuartz);
	mGem.value = 25;
	mCoin.value = 5;
	mQuartz.value = 100;

	/* NSprite */
	mpGem = new NSprite(WINDOW_WIDTH/2, 50 + 140, &SpriteResource::RequestResource("Item", "gem"));
	mpCoin = new NSprite(WINDOW_WIDTH/2, 50 + 250, &SpriteResource::RequestResource("Item", "coin"));
	mpQuartz = new NSprite(WINDOW_WIDTH/2, 50 + 370, &SpriteResource::RequestResource("Item", "quartz"));
	mpReady = new NSprite(WINDOW_WIDTH/2, 50 + 480, &SpriteResource::RequestResource("UI", "poll_ready_banner"));

	mExit = false; mReady = false;
	mEnter = true; mFadeout = false; mSkip = false;

	mFadeTimer.Start();
}

void CPollState::Cleanup()
{
	printf("CPollState Cleanup\n");
	SDL_FreeSurface(mpBackground);
	SDL_FreeSurface(banner_middle);
	SDL_FreeSurface(banner_side);
	delete mpGem;
	delete mpCoin;
	delete mpQuartz;
	delete mpReady;
}

void CPollState::Pause()
{
	printf("CPollState Pause\n");
}

void CPollState::Resume()
{
	printf("CPollState Resume\n");
}

void CPollState::KeyInput(const SDL_Event& rEvent)
{
	if (mExit) return;
	if (rEvent.key.keysym.sym == SDLK_z)
	{
		if (!mSkip)
			mSkip = true;
		if (mReady)
			mExit = true;
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
	else
	{
		if (TickCounter(mGem, 1, GameScore::Instance()->GetGemCount()))
			if (TickCounter(mCoin, 2, GameScore::Instance()->GetCoinCount()))
				if (TickCounter(mQuartz, 3, GameScore::Instance()->GetQuartzCount()))
					mReady = true;
	}
	mpGem->Update(); mpCoin->Update(); mpQuartz->Update();
	mpReady->Update();
	CPlayState::Instance()->mpInterface->Update(rDeltaTime);
}

void CPollState::Reset(Tally& rItem)
{
	rItem.countPoint = Point(0,0);
	rItem.totalPoint = Point(0,0);
	rItem.count = 0;
	rItem.total = 0;
	rItem.value = 0;
	rItem.visible = false;
	rItem.countStr.str("0");
	rItem.totalStr.str("0");
}

bool CPollState::TickCounter(Tally& rItem, int counterType, int countleft)
{
	int decrement = countleft > 5 ? 5: 1;
	rItem.visible = true;
	if (mSkip)
		decrement = countleft;
	if (countleft >= 1)
	{
		GameScore::Instance()->IncreaseScore(rItem.value * decrement);
		GameScore::Instance()->DecreaseCounter(decrement, counterType);
		rItem.total += rItem.value * decrement;
		rItem.count += decrement;
		rItem.totalStr.str("");
		rItem.totalStr << rItem.total;
		rItem.countStr.str("");
		rItem.countStr << "x" << rItem.count;
		return false;
	}
	else
		return true;
}

void CPollState::Draw(SDL_Surface* pdest) 
{
	Shared::DrawSurface(0, 0, mpBackground, pdest);

	Shared::DrawSurface(banner_left_pos.x, banner_left_pos.y, banner_side, pdest);
	Shared::DrawSurface(banner_right_pos.x, banner_right_pos.y, banner_side, pdest);
	Shared::DrawSurface(banner_middle_pos.x, banner_middle_pos.y, banner_middle, pdest);

	if (mGem.visible)
	{
		mpFont->pFont->draw(banner_left_pos.x + 20, 180, mGem.countStr.str().c_str());
		mpFont->pFont->draw(banner_right_pos.x + 20, 180, mGem.totalStr.str().c_str());
		mpGem->Draw(pdest);
	}
	if (mCoin.visible) 
	{
		mpFont->pFont->draw(banner_left_pos.x + 20, 300, mCoin.countStr.str().c_str());
		mpFont->pFont->draw(banner_right_pos.x + 20, 300, mCoin.totalStr.str().c_str());
		mpCoin->Draw(pdest);
	}
	if (mQuartz.visible)
	{
		mpFont->pFont->draw(banner_left_pos.x + 20, 400, mQuartz.countStr.str().c_str());
		mpFont->pFont->draw(banner_right_pos.x + 20, 400, mQuartz.totalStr.str().c_str());
		mpQuartz->Draw(pdest);
	}
	if (mReady && !mExit)
		mpReady->Draw(pdest);
	
	SPG_RectFilledBlend(pdest, GAME_BANNER_WIDTH, 0, GAME_BOUNDS_WIDTH, WINDOW_HEIGHT, 16777215, mAlpha);

	CPlayState::Instance()->mpInterface->Draw(pdest);
}
