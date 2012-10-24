#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Engine/Engine.h"

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

	void ChangeState(CEngine* game, CGameState* state) {
		game->ChangeState(state);
	}
protected:
   	CGameState() { }
};

#endif