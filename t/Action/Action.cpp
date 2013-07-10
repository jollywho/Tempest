#include "Action.h"
#include "Enemy/Enemy.h"
#include "State/PlayState.h"

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