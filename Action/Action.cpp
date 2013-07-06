#include "Action.h"
#include "Enemy/Enemy.h"
#include "State/PlayState.h"
#include "Pattern/ERotBullet.h"

Action::Action()
{
	mDel = false;
	mNext = false;
}

Action::Action(bool del, int loops)
{
	mNext = false;
	mDel = del;
	mLoops = loops;
}

Action::~Action()
{

}

void Action::Update(Enemy& enemy, Uint32 deltaTicks)
{
	if (enemy.IsHit())
	{
		SDL_Rect rec = enemy.GetBounds();
		CPlayState::Instance()->en_bulletlist.push_back(new ERotBullet(rec.x, rec.y, 0, "Arrow.png"));
		mNext =  true;
	}
}