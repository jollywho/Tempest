#pragma once
#ifndef CONTINUESTATE_H
#define CONTINUESTATE_H

#include "gamestate.h"
#include "Engine/Timer.h"

class NSprite;
class Menu;
struct FontInfo;

class CContinueState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause(){}
	void Resume(){}
	void Back(){}

	void KeyInput(const KeyStruct& rKeys);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pDest);

	static CContinueState* Instance() {
		return &mContState;
	}

protected:
	CContinueState() { }
private:
	static CContinueState mContState;
	FontInfo* mpFont;
    int mAlpha;
	char countdown[9];
	int mCount;
	Timer mCountdownTimer;
	Timer mFadeTimer;
	Timer mTitleTimer;

	bool mEnter; 
	bool mFadeout; 
	bool mSpan;

	NSprite* mpTitle;
	SDL_Surface* mpContTitle;
	SDL_Surface* mpContCount;
	SDL_Surface* mpScreen;
	SDL_Rect mScreenBounds;
    Menu* mpMenu;
};

#endif