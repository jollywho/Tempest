#include "pausestate.h"
#include <sprig.h>
#include "UI/Menu.h"

CPauseState CPauseState::m_PauseState;

void CPauseState::Init()
{
	printf("CPauseState Init\n");

	ClearRequest();
	screen = SDL_DisplayFormatAlpha(SPG_CopySurface(SDL_GetVideoSurface()));

	screen_bounds.x = _G_BANNER_WIDTH;
	screen_bounds.y = 0;
	screen_bounds.w = _GSCREEN_WIDTH;
	screen_bounds.h = _GSCREEN_HEIGHT;

	alpha = 0;

    main_menu = new Menu();
	//
    main_menu->AddItem(_WSCREEN_WIDTH/2, 200, "Return");
    main_menu->AddItem(_WSCREEN_WIDTH/2, 260, "Options");
	main_menu->AddItem(_WSCREEN_WIDTH/2, 320, "Quit to Menu");
    main_menu->AddItem(_WSCREEN_WIDTH/2, 380, "Exit Game");

	entering = true; fadeout = false; span = false;
	submenu = false;

	fade_timer.start();
}

void CPauseState::Cleanup()
{
	printf("CPauseState Cleanup\n");
	SDL_FreeSurface(screen);
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
	if (fade_timer.get_ticks() > 10)
	{
		if (alpha < 100) alpha+=5;
		fade_timer.start();
	}
}

void CPauseState::Draw(SDL_Surface* dest)
{
	Shared::apply_surface(_G_BANNER_WIDTH, 0, screen, dest, &screen_bounds);
	SPG_RectFilledBlend(dest, _G_BANNER_WIDTH, 0, _G_BOUNDS_WIDTH, _G_BOUNDS_HEIGHT, 0, alpha);
	if (!submenu) main_menu->Draw(dest);
}
