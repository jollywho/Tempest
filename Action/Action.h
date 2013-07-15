#pragma once
#ifndef ACTION_H
#define ACTION_H

#include "Engine/Shared.h"

class Enemy;

class Action
{
protected:
	bool mNext;
	bool mDel; //this is for one-time-only actions
	int mLoops;
public:
	Action();
	Action(bool del, int loops);
	virtual ~Action(){};
	virtual void Update(Enemy& enemy, Uint32 deltaTicks){};
	inline bool RequestNext() { 
		mLoops != -1 && mLoops > 0 ? mLoops--, mNext = true : 0; 
		return mNext; };
	bool RequestDelete() { return mDel; };
	bool IsLoopAction() { return mLoops > 0 ? 1 : 0; };
	int ActionCount() { return mLoops; };
};


#endif

