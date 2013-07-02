#pragma once
#ifndef ACTION_H
#define ACTION_H

#include "Engine/Shared.h"

class Enemy;

class Action
{
protected:
	bool mNext;
public:
	virtual ~Action() {};
	virtual void Update(Enemy& enemy, Uint32 deltaTicks) = 0;
	bool RequestNext() { return mNext; };
};


#endif

