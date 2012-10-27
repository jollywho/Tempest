#pragma once
#ifndef EROTBULLET_H
#define EROTBULLET_H

#include <string>
#include "EnemyBullet.h"

class ERotBullet : public EnemyBullet
{
public:
	ERotBullet(float x, float y, int angl, std::string id);
	~ERotBullet() {}
	void Update( const int& iElapsedTime );
    void Draw(SDL_Surface *dest);
private:
	float xVel2; float yVel2;
	int angle;
};

#endif