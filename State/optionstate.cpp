#include "optionstate.h"
#include "Engine/NFont.h"
#include "UI/Menu.h"
#include "Engine/SpriteResource.h"
#include "Game/SaveScore.h"
#include "Game/GameScore.h"
#include "Engine/SFX.h"

COptionState COptionState::m_OptionState;

void COptionState::Init()
{
	printf("COptionState Init\n");
	ClearRequest();
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	selector_surface = Shared::load_image("Image/UI/SoundSelector.png");
	frame_surface = Shared::load_image("Image/UI/SoundFrame.png");


	font_surface = Shared::load_image("Font/GoldMistral.png");
	score_font_surface = Shared::load_image("Font/BlueHigh.png");
	font = new NFont(SDL_GetVideoSurface(), font_surface);
	score_font = new NFont(SDL_GetVideoSurface(), score_font_surface);

	int h = font->getHeight("BGM");
	int w = font->getWidth("BGM");
	int menuheight = _WSCREEN_HEIGHT/2 - (h * 6)/2 - 84; //offset by top and bottom banners
	align_x = _WSCREEN_WIDTH/2 - w*2.5;

	bgm_frame.x = align_x + w*2;
	bgm_frame.y = 140 - ( FRAME_HEIGHT/2);
	fx_frame.x = align_x + w*2;
	fx_frame.y = 200 - ( FRAME_HEIGHT/2);

	bgm_selector.y = bgm_frame.y + (FRAME_HEIGHT/2 - SELECTOR_HEIGHT/2);
	fx_selector.y = fx_frame.y + (FRAME_HEIGHT/2 - SELECTOR_HEIGHT/2);

	bgm_selector.x = bgm_frame.x + (((double)SFX::SetBGM(0)/MIX_MAX_VOLUME)*235);
	fx_selector.x = fx_frame.x + (((double)SFX::SetFX(0)/MIX_MAX_VOLUME)*235);

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
	SDL_FreeSurface(selector_surface);
	SDL_FreeSurface(frame_surface);
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

	Shared::apply_surface(bgm_frame.x,bgm_frame.y,frame_surface,dest);
	Shared::apply_surface(bgm_selector.x,bgm_selector.y,selector_surface,dest);

	Shared::apply_surface(fx_frame.x,fx_frame.y,frame_surface,dest);
	Shared::apply_surface(fx_selector.x,fx_selector.y,selector_surface,dest);
}