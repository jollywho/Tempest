#pragma once
#ifndef MOVE_H
#define MOVE_H

#include "Action.h"

enum Moves
{
	MV_STRAIGHT,
	MV_DIAG,
	MV_CURVE
};

enum Direction
{
	Up, Down, Left, Right
};

class Move : public Action
{
private:
	Point mDestination;
	int mSpeed;
	Moves mMoveId;
	Timer mTimer;
	Direction mDir;
public:
	void Update(Enemy& enemy, Uint32 deltaTicks);
	Move();
	~Move();
};


#endif

