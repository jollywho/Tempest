#include "pausestate.h"
#include <sprig.h>
#include "UI/Menu.h"

CPauseState CPauseState::mPauseState;

void CPauseState::Init()
{
	printf("CPauseState initialize\n");

	ClearRequest();
	mpScreen = SDL_DisplayFormatAlpha(SPG_CopySurface(SDL_GetVideoSurface()));

	mScreenBounds.x = GAME_BANNER_WIDTH;
	mScreenBounds.y = 0;
	mScreenBounds.w = GAMESCREEN_WIDTH;
	mScreenBounds.h = GAMESCREEN_HEIGHT;

	mAlpha = 0;

    mpMenu = new Menu();
	//
    mpMenu->AddItem(WINDOW_WIDTH/2, 200, "Return");
    mpMenu->AddItem(WINDOW_WIDTH/2, 260, "Options");
	mpMenu->AddItem(WINDOW_WIDTH/2, 320, "Quit to Menu");
    mpMenu->AddItem(WINDOW_WIDTH/2, 380, "Exit Game");

	mEnter = true; 
	mFadeout = false; 
	mSpan = false;
	mSubmenu = false;

	mFadeTimer.Start();
}

void CPauseState::Cleanup()
{
	printf("CPauseState Cleanup\n");
	SDL_FreeSurface(mpScreen);
	delete mpMenu;
}

void CPauseState::Pause()
{
	printf("CPauseState Pause\n");
}

void CPauseState::Resume()
{
	printf("CPauseState Resume\n");
}

void CPauseState::Back()
{
	printf("CPauseState Return\n");
	mSubmenu = false;
}

void CPauseState::KeyInput(const KeyStruct& rKeys)
{
	if (rKeys.esc) PopState();
	if (rKeys.z)
	{
		mpMenu->Select();
		if (mpMenu->GetIndex() == 1) { PopState(); }
		if (mpMenu->GetIndex() == 2) { PushMenu(State::Option); mSubmenu = true; mpMenu->Reset(); }
		if (mpMenu->GetIndex() == 3) { ChangeState(State::Intro); }
		if (mpMenu->GetIndex() == 4) { SDL_Quit(); } //todo: are you sure?
	}
	if (rKeys.down) mpMenu->MoveIndex(1);
	else if (rKeys.up) mpMenu->MoveIndex(-1);
}

void CPauseState::Update(const int& rDeltaTime)
{
	mpMenu->Update(rDeltaTime, mAlpha);
	if (mFadeTimer.GetTicks() > 10)
	{
		if (mAlpha < 100) mAlpha+=5;
		mFadeTimer.Start();
	}
}

void CPauseState::Draw(SDL_Surface* pDest)
{
	Shared::DrawSurface(GAME_BANNER_WIDTH, 0, mpScreen, pDest, &mScreenBounds);
	SPG_RectFilledBlend(pDest, GAME_BANNER_WIDTH, 0, GAME_BOUNDS_WIDTH, GAME_BOUNDS_HEIGHT, 0, mAlpha);
	if (!mSubmenu) mpMenu->Draw(pDest);
}
