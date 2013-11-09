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
#include "IntroState.h"
#include "Engine/Shared.h"
#include "UI/Menu.h"
#include "Sprig.h"
#include "Engine/SpriteResource.h"
#include "UI/Decor.h"
#include "ScorePanel.h"
#include "OptionPanel.h"
#include "ModeSelectPanel.h"

CIntroState CIntroState::mIntroState;

void CIntroState::Init()
{
	printf("CIntroState Init\n");
	ClearRequest();
	mpBackgroundSurface =  Shared::LoadImage("Image/UI/IntroBG.png");

	mpBorderTop = Shared::LoadImage("Image/UI/intro_border_top.png");
	mpBorderBot =  Shared::LoadImage("Image/UI/intro_border_bot.png");

	mAlpha = 255;

	for(int i=0; i<50; i++)
		mpDecorList[i] = new Decor();

    mpMenu = new Menu();
	//
    mpMenu->AddItem(WINDOW_WIDTH/2, 200, "New Game");
    mpMenu->AddItem(WINDOW_WIDTH/2, 260, "Stage Jump");
	mpMenu->AddItem(WINDOW_WIDTH/2, 320, "Results");
    mpMenu->AddItem(WINDOW_WIDTH/2, 380, "Options");
    mpMenu->AddItem(WINDOW_WIDTH/2, 440, "Exit");

	mBackground.x = 0; mBackground2.x = -1280;
	mBorderTop = -42; mBorderBot = WINDOW_HEIGHT;
	mBorderleft = -160; mBorderright = WINDOW_WIDTH;

	mExit = false; 
	mEnter = true; 
	mFadeout = false; 
	mSpan = false;

	mFadeTimer.Start();
}

void CIntroState::Cleanup()
{
	printf("CIntroState Cleanup\n");
    delete mpMenu;
	for(int i=0; i<50; i++)
		delete mpDecorList[i];
	SDL_FreeSurface(mpBackgroundSurface);
	SDL_FreeSurface(mpBorderTop);
	SDL_FreeSurface(mpBorderBot);
	if (mpPanel != NULL) {
		delete mpPanel;
		mpPanel = NULL;
	}
}

void CIntroState::Back()
{
	printf("CIntroState Return\n"); //todo delete
}

void CIntroState::KeyInput(const SDL_Event& rEvent)
{
	if (mExit) return;
	if (mpPanel != NULL) 
	{
		mpPanel->KeyInput(rEvent);
	}
	else
	{
		if (rEvent.key.keysym.sym == SDLK_ESCAPE)
		{
			if (mpMenu->GetIndex() == mpMenu->Count())
			{
				SDL_Event event_quit; event_quit.type = SDL_QUIT;  SDL_PushEvent(&event_quit);
			}
			else  
				mpMenu->SetIndex(mpMenu->Count());
		}
		if (1)
		//if (rEvent.z) debug
		{
			mpMenu->Select();
			if (mpMenu->GetIndex() == 1) { mpPanel = new ModeSelectPanel(); }
			if (mpMenu->GetIndex() == 3) { mpPanel = new ScorePanel(); }
			if (mpMenu->GetIndex() == 4) { mpPanel = new OptionPanel(); }
			if (mpMenu->GetIndex() == 5) { SDL_Event event_quit; event_quit.type = SDL_QUIT;  SDL_PushEvent(&event_quit); }
		}
		if (rEvent.key.keysym.sym == SDLK_DOWN) mpMenu->MoveIndex(1);
		else if (rEvent.key.keysym.sym == SDLK_UP) mpMenu->MoveIndex(-1);
	}
}

void CIntroState::MenuAction()
{
	mAlpha = 0;
	mExit = true; 
	mSpan = true; 
	mFadeout = true;

}

void CIntroState::Update(const int& rDeltaTime) 
{
	if (mpPanel != NULL)
	{
		if (mpPanel->Forward() && !mExit)
			MenuAction();
		if (mpPanel->Back())
		{
			mpMenu->Reset();
			delete mpPanel;
			mpPanel = NULL;
		}
		else
			mpPanel->Update(rDeltaTime);
	}

	mpMenu->Update(rDeltaTime, mAlpha);
	for(int i=0; i<50; i++)
		mpDecorList[i]->Update(rDeltaTime);

	mBackground.x += 1; mBackground2.x += 1;
	if (mBackground.x > WINDOW_WIDTH) 
		mBackground.x = mBackground2.x - 1280;
	if (mBackground2.x > WINDOW_WIDTH) 
		mBackground2.x = mBackground.x - 1280;

	if (mEnter)
	{
		if (!mSpan && mBorderTop < 0)
		{
			mBorderTop+=2;
			mBorderBot-=2;
		}
		else if (mAlpha > 0) 
		{
			if (mFadeTimer.GetTicks() > 10) 
			{
				mAlpha-=5;
				mFadeTimer.Start(); 
			} 
		}
		else
			mEnter = false;
	}
	if (mExit)
	{
		if (mSpan && mBorderleft < 0)
		{
			mBorderleft+=2;
			mBorderright-=2;
			mBorderTop-=2;
			mBorderBot+=2;
		}
		else if (mFadeout && mAlpha < 255) 
		{
			if (mFadeTimer.GetTicks() > 10) 
			{
				mAlpha+=5;
				mFadeTimer.Start(); 
			} 
		}
		else
			ChangeState(State::PLAY);
	}
}

void CIntroState::Draw(SDL_Surface* pdest) 
{
	Shared::DrawSurface(mBackground.x, 0, mpBackgroundSurface, pdest);
	Shared::DrawSurface(mBackground2.x, 0, mpBackgroundSurface, pdest);

	for(int i=0; i<50; i++)
		mpDecorList[i]->Draw(pdest);

	if (mpPanel == NULL && !mExit)
		mpMenu->Draw(pdest);
	else
		mpPanel->Draw(pdest);
	
	SPG_RectFilledBlend(pdest,0,0,WINDOW_WIDTH,WINDOW_HEIGHT, 0, mAlpha);

	Shared::DrawSurface(0, mBorderTop, mpBorderTop, pdest);
	Shared::DrawSurface(0, mBorderBot, mpBorderBot, pdest);

	//Shared::DrawSurface(mBorderleft, 0, mpBorderleft, pdest);
	//Shared::DrawSurface(mBorderright, 0, mpBorderright, pdest);

	if (mpPanel != NULL)
		mpPanel->DrawTop(pdest);
}
