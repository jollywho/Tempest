#include "optionstate.h"
#include "Engine/NFont.h"
#include "UI/Menu.h"
#include "Engine/SpriteResource.h"
#include "Game/SaveScore.h"
#include "Game/GameScore.h"
#include "Engine/SFX.h"

COptionState COptionState::mOptionState;

void COptionState::Init()
{
	printf("COptionState initialize\n");
	ClearRequest();
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	mpSelector = Shared::LoadImage("Image/UI/SoundSelector.png");
	mpFrame = Shared::LoadImage("Image/UI/SoundFrame.png");

	mpFontSurface = Shared::LoadImage("Font/GoldMistral.png");
	mpFont = new NFont(SDL_GetVideoSurface(), mpFontSurface);

	int h = mpFont->getHeight("BGM");
	int w = mpFont->getWidth("BGM");
	int menuheight = WINDOW_HEIGHT/2 - (h * 6)/2 - 84; //offset by top and bottom banners
	mAlignX = WINDOW_WIDTH/2 - w*2.5;

	/* Frames */
	mBgmFrame.x = mAlignX + w*2;
	mBgmFrame.y = 140 - ( FRAME_HEIGHT/2);
	mSfxFrame.x = mAlignX + w*2;
	mSfxFrame.y = 200 - ( FRAME_HEIGHT/2);

	mBgmSelector.y = mBgmFrame.y + (FRAME_HEIGHT/2 - SELECTOR_HEIGHT/2);
	mSfxSelector.y = mSfxFrame.y + (FRAME_HEIGHT/2 - SELECTOR_HEIGHT/2);

	mBgmSelector.x = mBgmFrame.x + (((double)SFX::BgmVolume(0)/MIX_MAX_VOLUME)*235);
	mSfxSelector.x = mSfxFrame.x + (((double)SFX::SfxVolume(0)/MIX_MAX_VOLUME)*235);

	mpMenu = new Menu();
	mpMenu->AddItem(mAlignX, 140, "BGM");
	mpMenu->AddItem(mAlignX, 200, "SFX");
	mpMenu->AddItem(mAlignX, 260, "Mode");
	mpMenu->AddItem(mAlignX, 320, "Key Config");
	mpMenu->AddItem(mAlignX, 380, "Defaults");
	mpMenu->AddItem(mAlignX, 440, "Return");
}

void COptionState::Cleanup()
{
	printf("COptionState Cleanup\n");
	SDL_EnableKeyRepeat(0, 0);
	SDL_FreeSurface(mpFontSurface);
	SDL_FreeSurface(mpSelector);
	SDL_FreeSurface(mpFrame);
	delete mpFont;
}

void COptionState::KeyInput(const KeyStruct& rKeys)
{
	if (rKeys.esc) PopMenu();
	if (rKeys.z)
	{
		mpMenu->Select();
		if (mpMenu->GetIndex() == 1) {  }
		if (mpMenu->GetIndex() == 2) {  }
		if (mpMenu->GetIndex() == 3) {  }
		if (mpMenu->GetIndex() == 4) {  }
		if (mpMenu->GetIndex() == 5) {  }
		if (mpMenu->GetIndex() == 6) {  }
	}
	if (rKeys.down) mpMenu->MoveIndex(1);
	else if (rKeys.up) mpMenu->MoveIndex(-1);
}

void COptionState::Update(const int& rDeltaTime) 
{
	mpMenu->Update(rDeltaTime, 255);
}

void COptionState::Draw(SDL_Surface* pDest) 
{
	mpMenu->Draw(pDest);

	Shared::DrawSurface(mBgmFrame.x,mBgmFrame.y,mpFrame,pDest);
	Shared::DrawSurface(mBgmSelector.x,mBgmSelector.y,mpSelector,pDest);

	Shared::DrawSurface(mSfxFrame.x,mSfxFrame.y,mpFrame,pDest);
	Shared::DrawSurface(mSfxSelector.x,mSfxSelector.y,mpSelector,pDest);
}