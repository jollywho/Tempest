#include "Attack.h"
#include "Enemy/Enemy.h"
#include "State/PlayState.h"
#include "Pattern/ERotBullet.h"

Attack::Attack(int x)
{
	mSpeed = x;
	mNext = false;
}

Attack::~Attack()
{

}

void Attack::Update(Enemy& enemy, Uint32 deltaTicks)
{
	if (enemy.IsHit())
	{
		printf("Yes\n");
		SDL_Rect rec = enemy.GetBounds();
		CPlayState::Instance()->en_bulletlist.push_back(new ERotBullet(rec.x, rec.y, 0, "Arrow.png"));
		mNext =  true;
	}
}