#pragma once
#ifndef ATTACK_H
#define ATTACK_H

#include "Action.h"

class Attack : public Action
{
private:
	std::string mBulletId;
	int mSpeed;
	double mAngle;
	double mRot;
	std::string mSpriteId;
	int mAttackRate;
	Timer mTimer;
	Point mTarget;
public:
	Attack(int x);
	~Attack();
	void Update(Enemy& enemy, Uint32 deltaTicks);
};


#endif

