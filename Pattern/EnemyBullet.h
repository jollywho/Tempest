#pragma once
#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "Game/Bullet.h"

struct SpriteInfo;
struct RotationInfo;

class EnemyBullet : public Bullet
{
public:
	EnemyBullet(){};
	virtual ~EnemyBullet() {};
	static void Init();
    void DetectCollision();
    void Destroy();
protected:
	RotationInfo* info;
	static SpriteInfo* expinfo;
    bool bombed;
    float xVel, yVel;
    float xVal, yVal;
	void CheckBounds();
};

#endif