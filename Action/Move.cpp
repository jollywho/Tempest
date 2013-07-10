#include "Move.h"
#include "Enemy/Enemy.h"
#include "State/PlayState.h"

Move::Move(bool del, int move_type, int speed, int dest_x, int dest_y, int dir_type)
	: Action(del, 0)
{
	mMoveType = (Moves)move_type;
	mSpeed = speed;
	mDestx = dest_x;
	mDesty = dest_y;
	mDir = (Direction)dir_type;
}

Move::~Move()
{

}

void Move::Update(Enemy& enemy, Uint32 deltaTicks)
{
	if (enemy.IsHit())
	{
		enemy.MoveTo(Point(0,0));
		mNext =  true;
	}
}

void Move::ToTarget()
{
	/*
	float dx = (mDestx) - (mX);
	float dy = (mDesty) - (mY);
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));
	
	float xa = dx / Length;
	float ya = dy / Length;
	
	if (mDir == 1)
	{
		xa = xa * cos(mAngle);
		ya = ya * sin(mAngle);
	}
	
	mX += (xa * (mSpeed * (rDeltaTime / 1000.f)));
	mY += (ya * (mSpeed * (rDeltaTime / 1000.f)));
	*/
}