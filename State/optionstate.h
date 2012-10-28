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
	static const int FRAME_WIDTH = 256;
	static const int FRAME_HEIGHT = 20;
	static const int SELECTOR_WIDTH = 18;
	static const int SELECTOR_HEIGHT = 32;

	Menu* main_menu;
	NFont* font;
	NFont* score_font;
	SDL_Surface* font_surface;
	SDL_Surface* score_font_surface;
	SDL_Surface* selector_surface;
	SDL_Surface* frame_surface;

	int align_x;
	Point fx_frame;
	Point fx_selector;
	Point bgm_frame;
	Point bgm_selector;
};

#endif