#include "continuestate.h"
#include "UI/NSprite.h"
#include "Engine/FontResource.h"
#include "Engine/SpriteResource.h"
#include <sprig.h>
#include "UI/Menu.h"

CContinueState CContinueState::mContState;

void CContinueState::Init()
{
	printf("CContinueState Init\n");

	ClearRequest();
	mpScreen = SDL_DisplayFormatAlpha(SPG_CopySurface(SDL_GetVideoSurface()));
	mScreenBounds.x = GAME_BANNER_WIDTH;
	mScreenBounds.y = 0;
	mScreenBounds.w = GAMESCREEN_WIDTH;
	mScreenBounds.h = GAMESCREEN_HEIGHT;
	
	mpTitle = new NSprite(WINDOW_WIDTH/2, 195, &SpriteResource::RequestResource("UI", "cont_title"), false, true);
	mpCounter = new NSprite(WINDOW_WIDTH/2, 195 + 48, &SpriteResource::RequestResource("UI", "cont_counter"), true);
	mpContTitle = Shared::LoadImage("Image/UI/cont_title_frame.png");
	mpContCount = Shared::LoadImage("Image/UI/cont_count_frame.png");

	mAlpha = 0;

	/* Menu */
    mpMenu = new Menu();
    mpMenu->AddItem(WINDOW_WIDTH/2, 320, "Yes");
    mpMenu->AddItem(WINDOW_WIDTH/2, 380, "No");

	mEnter = true; 
	mFadeout = false; 
	mSpan = false;

	mCountdownTimer.Start();
	mFadeTimer.Start();
}

void CContinueState::Cleanup()
{
	printf("CContinueState Cleanup\n");
	SDL_FreeSurface(mpContTitle);
	SDL_FreeSurface(mpContCount);
	SDL_FreeSurface(mpScreen);
	delete mpMenu;
	delete mpTitle;
	delete mpCounter;
}

void CContinueState::KeyInput(const KeyStruct& rKeys)
{
	if (rKeys.z)
	{
		mpMenu->Select();
		if (mpMenu->GetIndex() == 1) { PopState(); }
		if (mpMenu->GetIndex() == 2) { ChangeState(State::Intro); } //todo: gameoverstate
	}
	if (rKeys.down) mpMenu->MoveIndex(1);
	else if (rKeys.up) mpMenu->MoveIndex(-1);
}

void CContinueState::Update(const int& rDeltaTime)
{
	mpMenu->Update(rDeltaTime, mAlpha);
	mpTitle->Update();
	mpCounter->Update();
	if (mpCounter->IsDone())
		PopState();
	if (mFadeTimer.GetTicks() > 10)
	{
		if (mAlpha < 100) mAlpha+=5;
		mFadeTimer.Start();
	}
}

void CContinueState::Draw(SDL_Surface* pDest)
{
	Shared::DrawSurface(GAME_BANNER_WIDTH, 0, mpScreen, pDest, &mScreenBounds);
	SPG_RectFilledBlend(pDest, GAME_BANNER_WIDTH, 0, GAME_BOUNDS_WIDTH, GAME_BOUNDS_HEIGHT, 0, mAlpha);
	mpMenu->Draw(pDest);
	Shared::DrawSurface(WINDOW_WIDTH/2 - 225, 150, mpContTitle, pDest);
	Shared::DrawSurface(WINDOW_WIDTH/2 - 98, 200, mpContCount, pDest);
	mpTitle->Draw(pDest);
	mpCounter->Draw(pDest);
}