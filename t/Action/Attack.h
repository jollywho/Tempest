#pragma once
#ifndef ATTACK_H
#define ATTACK_H

#include "Action.h"

class Attack : public Action
{
private:
	std::string mBulletId;
	int mSpeed;
	double mRot;
	std::string mSpriteId;
	int mInterval;
	Timer mTimer;
public:
	Attack(bool del, std::string bullet_id, int speed, int rot, int interval);
	~Attack();
	void Update(Enemy& enemy, Uint32 deltaTicks);
};


#endif

