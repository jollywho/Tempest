#include "Attack.h"
#include "Enemy/Enemy.h"
#include "State/PlayState.h"
#include "Pattern/EnemyBullet.h"

Attack::Attack(bool del, std::string bullet_id, int speed, int rot, int interval)
	: Action (del, 0)
{
	mBulletId = bullet_id;
	mSpeed = speed;
	mRot = rot;
	mInterval = interval;
	mTimer.Start();
}

Attack::~Attack()
{

}

void Attack::Update(Enemy& enemy, Uint32 deltaTicks)
{
	if (mTimer.GetTicks() > mInterval)
	{
		mTimer.Start();
		SDL_Rect rec = enemy.GetBounds();
		rec.x += rec.w/2;
		rec.y += rec.h/2;
		CPlayState::Instance()->en_bulletlist.push_back(new EnemyBullet(mBulletId, rec.x, rec.y, mRot));
		printf("~%i, %i\n", rec.x, rec.y);
	}
}