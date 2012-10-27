#pragma once
#ifndef EROTBULLET_H
#define EROTBULLET_H

#include <string>
#include "EnemyBullet.h"

class ERotBullet : public EnemyBullet
{
private:
	float xVel2; float yVel2;
	int angle;
public:
	~ERotBullet() {};
	ERotBullet(float x, float y, int angl, std::string id);
	void Update( Uint32 deltaTicks );
    void Draw(SDL_Surface *dest);
};

#endif