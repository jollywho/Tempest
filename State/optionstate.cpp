#include "optionstate.h"
#include "Engine/NFont.h"
#include "UI/Menu.h"
#include "Engine/SpriteResource.h"
#include "Game/SaveScore.h"
#include "Game/GameScore.h"

COptionState COptionState::m_OptionState;

void COptionState::Init()
{
	printf("COptionState Init\n");
	ClearRequest();
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	banner = Shared::load_image("Image/UI/ScoreBanner.png");
	font_surface = Shared::load_image("Font/GoldMistral.png");
	score_font_surface = Shared::load_image("Font/BlueHigh.png");
	font = new NFont(SDL_GetVideoSurface(), font_surface);
	score_font = new NFont(SDL_GetVideoSurface(), score_font_surface);

	int h = font->getHeight("BGM");
	int w = font->getWidth("BGM");
	int menuheight = _WSCREEN_HEIGHT/2 - (h * 6)/2 - 84; //offset by top and bottom banners
	align_x = _WSCREEN_WIDTH/2 - w*2.5;

	main_menu = new Menu();
	main_menu->AddItem(align_x, 140, "BGM");
	main_menu->AddItem(align_x, 200, "SFX");
	main_menu->AddItem(align_x, 260, "Mode");
	main_menu->AddItem(align_x, 320, "Key Config");
	main_menu->AddItem(align_x, 380, "Defaults");
	main_menu->AddItem(align_x, 440, "Return");
}

void COptionState::Cleanup()
{
	printf("COptionState Cleanup\n");
	SDL_EnableKeyRepeat(0, 0);
	SDL_FreeSurface(font_surface);
	SDL_FreeSurface(score_font_surface);
	SDL_FreeSurface(banner);
	delete font;
	delete score_font;
}

void COptionState::CheckKeys(const KeyStruct& keys)
{
	if (keys.esc) PopMenu();
	if (keys.z)
	{
		main_menu->Select();
		if (main_menu->GetIndex() == 1) {  }
		if (main_menu->GetIndex() == 2) {  }
		if (main_menu->GetIndex() == 3) {  }
		if (main_menu->GetIndex() == 4) {  }
		if (main_menu->GetIndex() == 5) {  }
		if (main_menu->GetIndex() == 6) {  }
	}
	if (keys.down) main_menu->SetIndex(1);
	else if (keys.up) main_menu->SetIndex(-1);
}

void COptionState::Update(const int& iElapsedTime) 
{
	main_menu->Update(iElapsedTime, 255);
}

void COptionState::Draw(SDL_Surface* dest) 
{
	main_menu->Draw(dest);
}