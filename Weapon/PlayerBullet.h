#ifndef PLAYERBULLTET_H
#define PLAYERBULLTET_H

#include "Game/Bullet.h"

class PlayerBullet : public Bullet
{
public:
    explicit PlayerBullet(float x, float y, int angl, int rots);
	virtual ~PlayerBullet(){}

	virtual void Update(const int& iElapsedTime) = 0;
	virtual void Draw(SDL_Surface *dest) = 0;
    
	bool RequestDelete() { return m_delete; };
    void CheckCollision();
	void CheckBounds(Point camera_pos);
protected:
	SDL_Rect offset;
	float xVel, yVel;
    float xVal, yVal;
    Timer clip_timer;
	int angle;

	static Point min_bounds;
	static Point max_bounds;
	
};

#endif