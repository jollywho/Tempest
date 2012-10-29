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

	virtual void Update(const int& rDeltaTime) = 0;
	virtual void Draw(SDL_Surface *pDest) = 0;

protected:
	RotationInfo* mpRotInfo;
	static SpriteInfo* mspExpInfo;
    float xvel, yvel;
    float mX, mY;
	void CheckBounds();
};

#endif