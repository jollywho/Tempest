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
	virtual void Back() = 0;

	virtual void KeyInput(const KeyStruct& rKeys) = 0;
	virtual void Update(const int& rDeltaTime) = 0;
	virtual void Draw(SDL_Surface* dest) = 0;

	void ClearRequest() { 
		mStateChange = false; 
		mStatePush = false;
		mStatePop = false;
		mMenuPush = false;
		mMenuPop = false;
	}

	void ChangeState(States::State id) {
		mRequestedState = id;
		mStateChange = true;
	}

	void PushState(States::State id) {
		mRequestedState = id;
		mStatePush = true;
	}

	void PopState()	{ 
		mStatePop = true; 
	}

	void PushMenu(States::State id) {
		mRequestedState = id;
		mMenuPush = true;
	}

	void PopMenu()	{ 
		mMenuPop = true; 
	}

	bool IsStateChange() { return mStateChange; }
	bool IsStatePush() { return mStatePush; }
	bool IsStatePop() { return mStatePop; }
	bool IsMenuPush() { return mMenuPush; }
	bool IsMenuPop()	{ return mMenuPop; }

	States::State RequestedState() { return mRequestedState; }
protected:
   	CGameState() { }
private:
	States::State mRequestedState;
	bool mStateChange;
	bool mStatePush;
	bool mStatePop;
	bool mMenuPush;
	bool mMenuPop;
};

#endif