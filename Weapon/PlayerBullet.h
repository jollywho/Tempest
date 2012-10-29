#ifndef PLAYERBULLTET_H
#define PLAYERBULLTET_H

#include "Game/Bullet.h"

class PlayerBullet : public Bullet
{
public:
    explicit PlayerBullet(float x, float y, int angl, int rots);
	virtual ~PlayerBullet(){}

	static void Init();
	virtual void Update(const int& rDeltaTime) = 0;
	virtual void Draw(SDL_Surface *pDest) = 0;
    
    void DetectCollision();
	void CheckBounds(Point camera_pos);
protected:
	
	SDL_Rect mOffset;
	float xvel, yvel;
    float mX, mY;
    Timer mClipTimer;
	int mAngle;

	static Point min_bounds;
	static Point max_bounds;
	
};

#endif