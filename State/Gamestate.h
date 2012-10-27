#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Engine/Engine.h"

enum State
{
	Intro,
	Play,
	Option,
	Poll,
	Name,
	GameOver,
};

class CGameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Return() = 0;

	virtual void CheckKeys(const KeyStruct& keys) = 0;
	virtual void Update(const int& iElapsedTime) = 0;
	virtual void Draw(SDL_Surface* dest) = 0;

	void PopState()	{ state_pop = true; }

	void PushState(State id) {
		request_state = id;
		state_push = true;
	}

	void ChangeState(State id) {
		request_state = id;
		state_change = true;
	}

	void PushMenu(State id) {
		request_state = id;
		menu_push = true;
	}

	void PopMenu()	{ menu_pop = true; }

	bool PopRequired() { return state_pop; }
	bool PushRequired() { return state_push; }
	bool StateRequired() { return state_change; }
	bool MenuPush() { return menu_push; }
	bool MenuPop()	{ return menu_pop; }

	State GetState() { return request_state; }

	void ClearRequest() { 
		state_change = false; 
		state_pop = false;
		state_push = false;
		menu_pop = false;
		menu_push = false;
	}
protected:
   	CGameState() { }
private:
	bool state_change;
	bool state_pop;
	bool state_push;
	bool menu_pop;
	bool menu_push;
	State request_state;
};

#endif