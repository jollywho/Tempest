#pragma once
#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "Gamestate.h"
#include "Engine/Timer.h"

class Menu;
class Decor;
class Panel;

class CIntroState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause() {}
	void Resume() {}
	void Back();

	void KeyInput(const KeyStruct& rKeys);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pDest);

	static CIntroState* Instance() {
		return &mIntroState;
	}
protected:
	CIntroState() { }
	void MenuAction();
private:
	static CIntroState mIntroState;
    Menu* mpMenu;
	Panel* mpPanel;
	SDL_Surface* mpBackgroundSurface;
	int mAlpha;
	Timer mFadeTimer;
	Point mBackground;
	Point mBackground2;

	float mBorderTop;
	float mBorderBot;
	float mBorderLeft;
	float mBorderRight;

	SDL_Surface* mpBorderTop;
	SDL_Surface* mpBorderBot;
	SDL_Surface* mpBorderLeft;
	SDL_Surface* mpBorderRight;

	Decor* mpDecorList[50];

	bool mEnter; 
	bool mExit; 
	bool mFadeout; 
	bool mSpan;
};

#endif