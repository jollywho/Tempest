#include "Move.h"
#include "Enemy/Enemy.h"
#include "State/PlayState.h"
#include "Pattern/ERotBullet.h"

Move::Move()
{
	mNext = false;
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