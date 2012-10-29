#include "intostate.h"
#include "Engine/Shared.h"
#include "UI/Menu.h"
#include "Sprig.h"
#include "Engine/SpriteResource.h"
#include "UI/Decor.h"

CIntroState CIntroState::mIntroState;

void CIntroState::Init()
{
	printf("CIntroState initialize\n");
	ClearRequest();
	mpBackgroundSurface =  Shared::LoadImage("Image/UI/IntroBG.png");
	SpriteResource::AddResource("UI", "decor.png", 48,48,100,8);

	mpBorderTop = Shared::LoadImage("Image/UI/intro_border_top.png");
	mpBorderBot =  Shared::LoadImage("Image/UI/intro_border_bot.png");
	mpBorderLeft = Shared::LoadImage("Image/UI/ui_border_left.png");
	mpBorderRight = Shared::LoadImage("Image/UI/ui_border_right.png");

	mAlpha = 255;

	for(int i=0; i<50; i++)
		mpDecorList[i] = new Decor("decor.png");

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
	mSubmenu = false;

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
}

void CIntroState::OpenSubMenu()
{
	mExit = false; 
	mSubmenu = true;
	mpMenu->Reset();
}

void CIntroState::Back()
{
	printf("CIntroState Return\n");
	mSubmenu = false;
}

void CIntroState::KeyInput(const KeyStruct& rKeys)
{
	if (mExit) return;
	if (rKeys.esc)
	{
		if (mpMenu->GetIndex() == mpMenu->Count()) 
			SDL_Quit();
		else  
			mpMenu->SetIndex(mpMenu->Count());
	}
	if (rKeys.z)
	{
		mpMenu->Select();
		mExit = true;
		mAlpha = 0;
		if (mpMenu->GetIndex() == 1) { mSpan = true; mFadeout = true; }
		if (mpMenu->GetIndex() == 3) { mFadeout = false; }
		if (mpMenu->GetIndex() == 4) { mFadeout = false; }
		if (mpMenu->GetIndex() == 5) { SDL_Quit; }
	}
	if (rKeys.down) mpMenu->MoveIndex(1);
	else if (rKeys.up) mpMenu->MoveIndex(-1);
}

void CIntroState::MenuAction()
{
	if (mpMenu->GetIndex() == 1) ChangeState(State::Play);
	//if (main_menu->GetIndex() == 2) RequestState(Poll);
	if (mpMenu->GetIndex() == 3) { PushMenu(State::Score); OpenSubMenu(); }
	if (mpMenu->GetIndex() == 4) { PushMenu(State::Option); OpenSubMenu(); }
}

void CIntroState::Update(const int& rDeltaTime) 
{
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
			MenuAction();
	}
}

void CIntroState::Draw(SDL_Surface* pDest) 
{
	Shared::DrawSurface(mBackground.x, 0, mpBackgroundSurface, pDest);
	Shared::DrawSurface(mBackground2.x, 0, mpBackgroundSurface, pDest);

	for(int i=0; i<50; i++)
		mpDecorList[i]->Draw(pDest);

	if (!mSubmenu) mpMenu->Draw(pDest);
	
	SPG_RectFilledBlend(pDest,0,0,WINDOW_WIDTH,WINDOW_HEIGHT, 0, mAlpha);

	Shared::DrawSurface(0, mBorderTop, mpBorderTop, pDest);
	Shared::DrawSurface(0, mBorderBot, mpBorderBot, pDest);

	Shared::DrawSurface(mBorderLeft, 0, mpBorderLeft, pDest);
	Shared::DrawSurface(mBorderRight, 0, mpBorderRight, pDest);
}
