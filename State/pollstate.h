#pragma once
#ifndef POLLSTATE_H
#define POLLSTATE_H

#include "gamestate.h"
#include "Engine/Timer.h"

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
	SDL_Surface* mpBackground;
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
};

#endif