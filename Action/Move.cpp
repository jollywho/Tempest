#include "Move.h"
#include "Enemy/Enemy.h"
#include "State/PlayState.h"

Move::Move(bool del, int move_type, int speed, int dest_x, int dest_y, int dir_type)
	: Action(del, -1)
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
	mNext = Straight(enemy, deltaTicks);
}

bool Move::Straight(Enemy& enemy, Uint32 deltaTicks)
{
	SDL_Rect temp = enemy.GetBounds();
	float dx = (mDestx) - (temp.x);
	float dy = (mDesty) - (temp.y);
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));
	if (Length > 50)
	{
		dx =  dx / Length; dy = dy /Length;
		enemy.Movement(dx * (mSpeed * (deltaTicks/1000.f)), dy * (mSpeed * (deltaTicks/1000.f)));
		return false;
	}
	if (Length < 5) 
		return true;
}