#pragma once
#ifndef POLLSTATE_H
#define POLLSTATE_H

#include "Gamestate.h"
#include "Engine/Timer.h"

class CPollState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();
	void Return() {};

	void CheckKeys(const KeyStruct& keys);
	void Update(const int& iElapsedTime);
	void Draw(SDL_Surface* dest);

	static CPollState* Instance() {
		return &m_IntroState;
	}
protected:
	CPollState() { }

private:
	static CPollState m_IntroState;
	SDL_Surface* bg;
	int alpha;
	Timer fade_timer;
	Point banner_middle_pos;
	Point banner_left_pos;
	Point banner_right_pos;

	SDL_Surface* banner_middle;
	SDL_Surface* banner_side;
	float banner_speed;
	bool exiting; bool entering; bool fadeout;
};

#endif