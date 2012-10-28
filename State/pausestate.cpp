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


	exiting = false; entering = true; fadeout = false; span = false;
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
}

void CPauseState::CheckKeys(const KeyStruct& keys)
{
	if (exiting) return;
	if (keys.esc) PopState();
	if (keys.z)
	{
		main_menu->Select();
		exiting = true;
		alpha = 0;
		if (main_menu->GetIndex() == 1) { PopState(); }
		if (main_menu->GetIndex() == 3) { ChangeState(S_INTRO); }
		if (main_menu->GetIndex() == 4) { fadeout = true; }
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
	main_menu->Draw(dest);
}
