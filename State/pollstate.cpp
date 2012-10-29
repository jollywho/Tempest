#include "Pollstate.h"
#include "Engine/Shared.h"
#include "Engine/FontResource.h"
#include "Engine/SpriteResource.h"
#include "Game/Gamescore.h"
#include "Game/Interface.h"
#include "Sprig.h"
#include "playstate.h"

CPollState CPollState::mIntroState;



void CPollState::Init()
{
	printf("CPollState initialize\n");
	ClearRequest();
	mpBackground =  Shared::LoadImage("Image/UI/poll.bmp");

	banner_middle = Shared::LoadImage("Image/UI/poll_banner_middle.png");
	banner_side = Shared::LoadImage("Image/UI/poll_banner_side.png");

	FontResource::AddFont("bobble_red.png");
	mpFont = &FontResource::RequestFont("bobble_red.png");

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
	mGem.value = 25;
	mCoin.value = 5;
	mQuartz.value = 100;

	/* NSprite */
	mpGem = new NSprite(WINDOW_WIDTH/2, 50 + 140, &SpriteResource::RequestResource("Items", "Gem.png"));
	mpCoin = new NSprite(WINDOW_WIDTH/2, 50 + 260, &SpriteResource::RequestResource("Items", "Coin.png"));
	mpQuartz = new NSprite(WINDOW_WIDTH/2, 50 + 360, &SpriteResource::RequestResource("Items", "Quartz.png"));

	mExit = false; mReady = false;
	mEnter = true; mFadeout = false;

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
	else
	{
		if (TickCounter(mGem, 1, GameScore::Instance()->GetGemCount()))
			if (TickCounter(mCoin, 2, GameScore::Instance()->GetCoinCount()))
				if (TickCounter(mQuartz, 3, GameScore::Instance()->GetQuartzCount()))
					mReady = true;
	}
	mpGem->Update(); mpCoin->Update(); mpQuartz->Update();
	CPlayState::Instance()->mpInterface->Update(rDeltaTime);
}

bool CPollState::TickCounter(Tally& rItem, int counterType, int countLeft)
{
	int decrement = countLeft > 5 ? 5: 1;
	
	if (countLeft >= 1)
	{
		GameScore::Instance()->IncreaseScore(rItem.value * decrement);
		GameScore::Instance()->DecreaseCounter(decrement, counterType);
		rItem.total += rItem.value * decrement;
		rItem.count += decrement;
		mGem.totalStr.str("");
		mGem.totalStr << mGem.total;
		mGem.countStr.str("");
		mGem.countStr << mGem.count;
		rItem.visible = false;
		return false;
	}
	else
	{
		rItem.visible = true;
		return true;
	}
}

void CPollState::Draw(SDL_Surface* pDest) 
{
	Shared::DrawSurface(0, 0, mpBackground, pDest);

	Shared::DrawSurface(banner_left_pos.x, banner_left_pos.y, banner_side, pDest);
	Shared::DrawSurface(banner_right_pos.x, banner_right_pos.y, banner_side, pDest);
	Shared::DrawSurface(banner_middle_pos.x, banner_middle_pos.y, banner_middle, pDest);

	mpFont->pFont->draw(banner_left_pos.x + 20, 180, mGem.totalStr.str().c_str());
	mpFont->pFont->draw(banner_right_pos.x + 20, 180, mGem.countStr.str().c_str());

	mpFont->pFont->draw(banner_left_pos.x + 20, 300, mCoin.totalStr.str().c_str());
	mpFont->pFont->draw(banner_right_pos.x + 20, 300, mCoin.countStr.str().c_str());

	mpFont->pFont->draw(banner_left_pos.x + 20, 400, mQuartz.totalStr.str().c_str());
	mpFont->pFont->draw(banner_right_pos.x + 20, 400, mQuartz.countStr.str().c_str());
	
	if (mGem.visible) mpGem->Draw(pDest);
	if (mCoin.visible) mpCoin->Draw(pDest);
	if (mQuartz.visible) mpQuartz->Draw(pDest);
	
	SPG_RectFilledBlend(pDest, GAME_BANNER_WIDTH, 0, GAME_BOUNDS_WIDTH, WINDOW_HEIGHT, 16777215, mAlpha);

	CPlayState::Instance()->mpInterface->Draw(pDest);
}
