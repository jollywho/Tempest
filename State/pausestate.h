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
	void Back();

	void KeyInput(const KeyStruct& rKeys);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pDest);

	static CPauseState* Instance() {
		return &mPauseState;
	}

protected:
	CPauseState() { }

private:
	static CPauseState mPauseState;
    int mAlpha;
    Menu* mpMenu;
	Timer mFadeTimer;
	SDL_Surface* mpScreen;
	SDL_Rect mScreenBounds;
	bool mEnter; 
	bool mFadeout; 
	bool mSpan;
	bool mSubmenu;

};

#endif