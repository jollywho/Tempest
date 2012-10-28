#include "pausestate.h"
#include <sprig.h>
#include "UI/Menu.h"

CPauseState CPauseState::m_PauseState;

void CPauseState::Init()
{
	printf("CPauseState Init\n");

	ClearRequest();
	bg =  Shared::load_image("Image/UI/pause.png");
	SDL_SetAlpha(bg,0,20);

	alpha = 255;

    main_menu = new Menu();
	//
    main_menu->AddItem(_WSCREEN_WIDTH/2, 200, "Return");
    main_menu->AddItem(_WSCREEN_WIDTH/2, 260, "Options");
	main_menu->AddItem(_WSCREEN_WIDTH/2, 320, "Quit to Menu");
    main_menu->AddItem(_WSCREEN_WIDTH/2, 440, "Exit Game");


	entering = true; fadeout = false; span = false;
	submenu = false;

	fade_timer.start();
	
}

void CPauseState::Cleanup()
{
	printf("CPauseState Cleanup\n");
	SDL_FreeSurface(bg);
	delete main_menu;
}

void CPauseState::Pause()
{
	printf("CPauseState Pause\n");
}

void CPauseState::Resume()
{
	printf("CPauseState Resume\n");
}

void CPauseState::Return()
{
	printf("CPauseState Return\n");
	submenu = false;
}

void CPauseState::CheckKeys(const KeyStruct& keys)
{
	if (keys.esc) PopState();
	if (keys.z)
	{
		main_menu->Select();
		alpha = 0;
		if (main_menu->GetIndex() == 1) { PopState(); }
		if (main_menu->GetIndex() == 2) { PushMenu(S_OPTION); submenu = true; main_menu->Reset(); }
		if (main_menu->GetIndex() == 3) { ChangeState(S_INTRO); }
		if (main_menu->GetIndex() == 4) { SDL_Quit(); } //todo: are you sure?
	}
	if (keys.down) main_menu->SetIndex(1);
	else if (keys.up) main_menu->SetIndex(-1);
}

void CPauseState::Update(const int& iElapsedTime)
{
	main_menu->Update(iElapsedTime, alpha);
}

void CPauseState::Draw(SDL_Surface* dest)
{
	Shared::apply_surface(_G_BANNER_WIDTH, 0, bg, dest);
	if (!submenu) main_menu->Draw(dest);
}
