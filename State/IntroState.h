#pragma once
#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "Gamestate.h"
#include "Engine/Timer.h"

class Menu;
class Decor;

class CIntroState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause() {}
	void Resume() {}
	void Return();

	void CheckKeys(const KeyStruct& keys);
	void Update(const int& iElapsedTime);
	void Draw(SDL_Surface* dest);

	static CIntroState* Instance() {
		return &m_IntroState;
	}
protected:
	CIntroState() { }
	void MenuAction();
private:
	static CIntroState m_IntroState;
    Menu* mainMenu;
	SDL_Surface* bg;
	int alpha;
	Timer fade_timer;
	float bgX; float bgX2;
	float border_top_y;
	float border_bot_y;
	float border_left_x;
	float border_right_x;

	SDL_Surface* border_top;
	SDL_Surface* border_bot;
	SDL_Surface* border_left;
	SDL_Surface* border_right;

	Decor* decor_list[50];

	bool exiting; bool entering; bool fadeout; bool span;
};

#endif