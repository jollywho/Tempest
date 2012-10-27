#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "Game/Bullet.h"

struct SpriteInfo;
struct RotationInfo;

class EnemyBullet : public Bullet
{
public:
	EnemyBullet();
	virtual ~EnemyBullet() {}
	static void Init();
    void DetectCollision();
    void Destroy();

	virtual void Update(const int& iElapsedTime) = 0;
	virtual void Draw(SDL_Surface *dest) = 0;

protected:
	RotationInfo* info;
	static SpriteInfo* expinfo;
    bool bombed;
    float xVel, yVel;
    float xVal, yVal;
	void CheckBounds();
};

#endif