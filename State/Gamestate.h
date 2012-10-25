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

	virtual void CheckKeys(const KeyStruct& keys) = 0;
	virtual void Update(const int& iElapsedTime) = 0;
	virtual void Draw(SDL_Surface* dest) = 0;

	void RequestState(State id) {
		request_state = id;
		change_required = true;
	}
	bool ChangeRequired() { return change_required; }
	State GetRequestedState() { return request_state; }
	void ClearRequest() { change_required = false; }
protected:
   	CGameState() { }
private:
	bool change_required;
	State request_state;
};

#endif