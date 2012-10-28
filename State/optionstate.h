#pragma once
#ifndef OPTIONSTATE_H
#define OPTIONSTATE_H

#include "Gamestate.h"
#include <sstream>

struct SpriteInfo;
class NFont;
class Menu;

class COptionState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause(){}
	void Resume(){}
	void Return(){}

	void CheckKeys(const KeyStruct& keys);
	void Update(const int& iElapsedTime);
	void Draw(SDL_Surface* dest);

	static COptionState* Instance() {
		return &m_OptionState;
	}
protected:
	COptionState() { }

private:
	static COptionState m_OptionState;
	Menu* main_menu;
	NFont* font;
	NFont* score_font;
	SDL_Surface* font_surface;
	SDL_Surface* score_font_surface;
	SDL_Surface* banner;

	int align_x;
};

#endif