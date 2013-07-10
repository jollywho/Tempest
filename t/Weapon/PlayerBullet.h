#ifndef PLAYERBULLTET_H
#define PLAYERBULLTET_H

#include "Game/Bullet.h"

struct RotationInfo;
struct SpriteInfo;

class PlayerBullet : public Bullet
{
public:
    explicit PlayerBullet(float x, float y, int angle, int rots);
	virtual ~PlayerBullet(){}

	static void Init();
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface *pDest);
    
    void DetectCollision();
	void CheckBounds(Point camera_pos);
protected:
	float xvel, yvel;
    float mX, mY;
    Timer mClipTimer;
	int mAngle;
	int mRots;
	static Point msMinBounds;
	static Point msMaxBounds;
	static RotationInfo* mpInfo;
	static SpriteInfo* _expInfo;
	SDL_Rect mOffset;
};

#endif