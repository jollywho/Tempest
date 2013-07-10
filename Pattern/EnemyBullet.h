#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "Game/Bullet.h"

struct SpriteInfo;
struct RotationInfo;

class EnemyBullet : public Bullet
{
public:
	EnemyBullet(std::string id, float x, float y, int angle, int ch_time=0, float xmod=1, float ymod=1, int angle2=0);
	~EnemyBullet();
    void DetectCollision();
    void Destroy();
	bool IsCollision(SDL_Rect obj);

	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface *pDest);

private:
	static const int TOO_FAR = 50;
	int mChangeTime;
	RotationInfo* mpRotInfo;
	static SpriteInfo* mspExpInfo;
    float xvel, yvel;
    float mX, mY;
	float mModx; float mMody;
	int mAngle; int mAngle2;
	void CheckBounds();
};

#endif