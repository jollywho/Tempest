#pragma once
#ifndef BULLETM
#define BULLETM
#include "PlayerBullet.h"
#include <string>

struct RotationInfo;
struct SpriteInfo;

class BulletM : public PlayerBullet
{
private:
	static RotationInfo* _info;
	static SpriteInfo* _expInfo;
public:
	BulletM(float x, float y, int angl, int rots);
	~BulletM(){}
	static void Init(std::string id, std::string expId);

	void Update(const int& iElapsedTime);
	void Draw(SDL_Surface *dest);

};

#endif