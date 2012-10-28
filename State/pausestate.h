#pragma once
#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "gamestate.h"
#include "Engine/Timer.h"

class Menu;

class CPauseState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();
	void Return();

	void CheckKeys(const KeyStruct& keys);
	void Update(const int& iElapsedTime);
	void Draw(SDL_Surface* dest);

	static CPauseState* Instance() {
		return &m_PauseState;
	}

protected:
	CPauseState() { }

private:
	static CPauseState m_PauseState;
    int alpha;
    Menu* main_menu;
	Timer fade_timer;
	SDL_Surface* screen;
	SDL_Rect screen_bounds;
	bool entering; bool fadeout; bool span;
	bool submenu;

};

#endif