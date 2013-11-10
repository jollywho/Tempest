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
#include "OptionPanel.h"
#include "Engine/NFont.h"
#include "UI/Menu.h"
#include "Engine/SpriteResource.h"
#include "Game/SaveScore.h"
#include "Game/GameScore.h"
#include "Engine/SFX.h"

OptionPanel::OptionPanel()
{
	printf("-OptionPanel Created-\n");
	mBack = false; mForward = false;

	mpSelector = Shared::LoadImage("Image/UI/SoundSelector.png");
	mpFrame = Shared::LoadImage("Image/UI/SoundFrame.png");

	mpFontSurface = Shared::LoadImage("Font/GoldMistral.png");
	mpFont = new NFont(SDL_GetVideoSurface(), mpFontSurface);

	int h = mpFont->getHeight("BGM");
	int w = mpFont->getWidth("BGM");
	int menuheight = WINDOW_HEIGHT / 2 - (h * 6) / 2 - 84; //offset by top and bottom banners
	mAlignX = WINDOW_WIDTH / 2 - w * 2.5;

	/* Frames */
	mBgmFrame.x = mAlignX + w * 2;
	mBgmFrame.y = 140 - (FRAME_HEIGHT / 2);
	mSfxFrame.x = mAlignX + w * 2;
	mSfxFrame.y = 200 - (FRAME_HEIGHT / 2);

	mBgmSelector.y = mBgmFrame.y + (FRAME_HEIGHT / 2 - SELECTOR_HEIGHT / 2);
	mSfxSelector.y = mSfxFrame.y + (FRAME_HEIGHT / 2 - SELECTOR_HEIGHT / 2);

	mBgmSelector.x = mBgmFrame.x + (((double)SFX::BgmVolume(0) / MIX_MAX_VOLUME) * 235);
	mSfxSelector.x = mSfxFrame.x + (((double)SFX::SfxVolume(0) / MIX_MAX_VOLUME) * 235);

	mpMenu = new Menu();
	mpMenu->AddItem(mAlignX, 140, "BGM");
	mpMenu->AddItem(mAlignX, 200, "SFX");
	mpMenu->AddItem(mAlignX, 260, "Mode");
	mpMenu->AddItem(mAlignX, 320, "Key Config");
	mpMenu->AddItem(mAlignX, 380, "Defaults");
	mpMenu->AddItem(mAlignX, 440, "Return");
}

OptionPanel::~OptionPanel()
{
	printf("-OptionPanel Deleted-\n");
	SDL_EnableKeyRepeat(0, 0);
	SDL_FreeSurface(mpFontSurface);
	SDL_FreeSurface(mpSelector);
	SDL_FreeSurface(mpFrame);
	delete mpFont;
	delete mpMenu;
}

void OptionPanel::KeyInput(const SDL_Event& rEvent)
{
	if (rEvent.key.keysym.sym == SDLK_ESCAPE) mBack = true;
	if (rEvent.key.keysym.sym == SDLK_z)
	{
		mpMenu->Select();
		if (mpMenu->GetIndex() == 1) {  }
		if (mpMenu->GetIndex() == 2) {  }
		if (mpMenu->GetIndex() == 3) {  }
		if (mpMenu->GetIndex() == 4) {  }
		if (mpMenu->GetIndex() == 5) {  }
		if (mpMenu->GetIndex() == 6) { mBack = true;}
	}
	if (rEvent.key.keysym.sym == SDLK_DOWN) mpMenu->MoveIndex(1);
	else if (rEvent.key.keysym.sym == SDLK_UP) mpMenu->MoveIndex(-1);
}

void OptionPanel::Update(const int& rDeltaTime) 
{
	mpMenu->Update(rDeltaTime, 255);
}

void OptionPanel::Draw(SDL_Surface* pdest) 
{
	mpMenu->Draw(pdest);

	Shared::DrawSurface(mBgmFrame.x,mBgmFrame.y,mpFrame,pdest);
	Shared::DrawSurface(mBgmSelector.x,mBgmSelector.y,mpSelector,pdest);

	Shared::DrawSurface(mSfxFrame.x,mSfxFrame.y,mpFrame,pdest);
	Shared::DrawSurface(mSfxSelector.x,mSfxSelector.y,mpSelector,pdest);
}