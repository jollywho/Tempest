#pragma once
#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "Gamestate.h"
#include "Engine/Timer.h"

class Menu;

class CIntroState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void CheckKeys(const KeyStruct& keys);
	void Update(const int& iElapsedTime);
	void Draw(SDL_Surface* dest);

	static CIntroState* Instance() {
		return &m_IntroState;
	}
protected:
	CIntroState() { }

private:
	static CIntroState m_IntroState;
    Menu* mainMenu;
	SDL_Surface* bg;
	int alpha;
	Timer fade_timer;
	float bgX; float bgX2;
};

#endif