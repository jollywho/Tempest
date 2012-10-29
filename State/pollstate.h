#pragma once
#ifndef POLLSTATE_H
#define POLLSTATE_H

#include "gamestate.h"
#include "Engine/Timer.h"
class FontInfo;

class CPollState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();
	void Back() {};

	void KeyInput(const KeyStruct& rKeys);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pDest);

	static CPollState* Instance() {
		return &mIntroState;
	}
protected:
	CPollState() { }

private:
	static CPollState mIntroState;
	FontInfo* mpFont;
	SDL_Surface* mpBackground;
	SDL_Surface* mpFontSurface;
	int mAlpha;
	Timer mFadeTimer;
	Point banner_middle_pos;
	Point banner_left_pos;
	Point banner_right_pos;

	SDL_Surface* banner_middle;
	SDL_Surface* banner_side;
	float banner_speed;
	bool mExit; 
	bool mEnter; 
	bool mFadeout;


	/*
	todo:
	1) Increment counter by 10/5/1
	2) Increase score by value
	3) Decrease interface count by counter
	*/
};

#endif