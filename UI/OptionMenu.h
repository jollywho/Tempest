#pragma once
#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include "Engine/Shared.h"

class Menu;

class OptionMenu
{
private:
	Timer exit_Timer;
	SDL_Surface* selector;
	SDL_Surface* frame;

	int align_x; int bgm_y;
	int bgmframe_x; int bgmframe_y;
	int bgmselector_x; int bgmselector_y;

	int fx_y;
	int fxframe_x; int fxframe_y;
	int fxselector_x; int fxselector_y;
public:
    OptionMenu();
	~OptionMenu();
	Menu* menu;
	bool exit_ready;

	void Update(Uint32 deltaTicks, int alpha);
    void Draw(SDL_Surface *dest);
	void Handle_input(SDL_Event event);
};
 

#endif
