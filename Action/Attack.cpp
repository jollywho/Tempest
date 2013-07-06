#include "Attack.h"
#include "Enemy/Enemy.h"
#include "State/PlayState.h"
#include "Pattern/ERotBullet.h"

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
	if (enemy.IsHit())
	{
		SDL_Rect rec = enemy.GetBounds();
		CPlayState::Instance()->en_bulletlist.push_back(new ERotBullet(rec.x, rec.y, 0, "Arrow.png"));
		mNext =  true;
	}
}