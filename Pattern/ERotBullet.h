#pragma once
#ifndef EROTBULLET_H
#define EROTBULLET_H

#include <string>
#include "EnemyBullet.h"

class ERotBullet : public EnemyBullet
{
public:
	ERotBullet(float x, float y, int angle, std::string id);
	~ERotBullet() {}
	void Update( const int& rDeltaTime );
    void Draw(SDL_Surface* pDest);
private:
	float xvel2; float yvel2;
	int mAngle;
};

#endif