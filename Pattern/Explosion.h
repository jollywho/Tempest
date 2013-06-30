#pragma once
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Engine/Shared.h"
#include <map>
#include <list>

struct SpriteInfo;
struct ExplosionInfo
{
	std::string id;
	int delay;
	int offsetX;
	int offsetY;
	int magnitude;
	bool residue;
};

class Explosion
{
private:
	SpriteInfo* info;
	int clip;
	int detTime;
	Timer clip_Timer;
	int altInterval;
	float xVal; float yVal;
	float xVel; float yVel;
	bool started;
	bool m_delete;
	static std::map<std::string, std::list<ExplosionInfo>> explosions;
public:
	Explosion(int x, int y, int xv, int yv, ExplosionInfo nfo);
    static void ClearList();
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *dest);
	bool RequestDelete() { return m_delete; };
	static void AddExplosionInfo(std::string enemyID, std::string expID, int magnitude, 
		int delay, int offsetX=0, int offsetY=0, bool residue=false);
	static void RequestExplosion(std::string enemyID, int x, int y, int xv, int yv);
};


#endif

