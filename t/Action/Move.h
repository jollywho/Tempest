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
	Up = 	1, 
	Down =	2, 
	Left =	3, 
	Right =	4,
};

class Move : public Action
{
private:
	int mDestx;
	int mDesty;
	int mSpeed;
	Moves mMoveType;
	Timer mTimer;
	Direction mDir;
public:
	Move(bool del, int move_type, int speed, int dest_x, int dest_y, int dir_type);
	~Move();
	void Update(Enemy& enemy, Uint32 deltaTicks);
};


#endif

