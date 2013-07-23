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
	mpBorderLeft = Shared::LoadImage("Image/UI/ui_border_left.png");
	mpBorderRight = Shared::LoadImage("Image/UI/ui_border_right.png");

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
	mBorderLeft = -160; mBorderRight = WINDOW_WIDTH;

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
	SDL_FreeSurface(mpBorderLeft);
	SDL_FreeSurface(mpBorderRight);
	if (mpPanel != NULL) {
		delete mpPanel;
		mpPanel = NULL;
	}
}

void CIntroState::Back()
{
	printf("CIntroState Return\n"); //todo delete
}

void CIntroState::KeyInput(const KeyStruct& rKeys)
{
	if (mExit) return;
	if (mpPanel != NULL) 
	{
		mpPanel->KeyInput(rKeys);
	}
	else
	{
		if (rKeys.esc)
		{
			if (mpMenu->GetIndex() == mpMenu->Count())
			{
				SDL_Event event_quit; event_quit.type = SDL_QUIT;  SDL_PushEvent(&event_quit);
			}
			else  
				mpMenu->SetIndex(mpMenu->Count());
		}
		if (1)
		//if (rKeys.z) debug
		{
			mpMenu->Select();
			if (mpMenu->GetIndex() == 1) { mpPanel = new ModeSelectPanel(); }
			if (mpMenu->GetIndex() == 3) { mpPanel = new ScorePanel(); }
			if (mpMenu->GetIndex() == 4) { mpPanel = new OptionPanel(); }
			if (mpMenu->GetIndex() == 5) { SDL_Event event_quit; event_quit.type = SDL_QUIT;  SDL_PushEvent(&event_quit); }
		}
		if (rKeys.down) mpMenu->MoveIndex(1);
		else if (rKeys.up) mpMenu->MoveIndex(-1);
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
		if (mSpan && mBorderLeft < 0)
		{
			mBorderLeft+=2;
			mBorderRight-=2;
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
			ChangeState(State::Play);
	}
}

void CIntroState::Draw(SDL_Surface* pDest) 
{
	Shared::DrawSurface(mBackground.x, 0, mpBackgroundSurface, pDest);
	Shared::DrawSurface(mBackground2.x, 0, mpBackgroundSurface, pDest);

	for(int i=0; i<50; i++)
		mpDecorList[i]->Draw(pDest);

	if (mpPanel == NULL && !mExit)
		mpMenu->Draw(pDest);
	else
		mpPanel->Draw(pDest);
	
	SPG_RectFilledBlend(pDest,0,0,WINDOW_WIDTH,WINDOW_HEIGHT, 0, mAlpha);

	Shared::DrawSurface(0, mBorderTop, mpBorderTop, pDest);
	Shared::DrawSurface(0, mBorderBot, mpBorderBot, pDest);

	//Shared::DrawSurface(mBorderLeft, 0, mpBorderLeft, pDest);
	//Shared::DrawSurface(mBorderRight, 0, mpBorderRight, pDest);

	if (mpPanel != NULL)
		mpPanel->DrawTop(pDest);
}
