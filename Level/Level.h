#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include "Engine/Engine.h"


class Layer;
class Enemy;

class Level
{
public:
	Level();
	~Level();
    void Update(const int& rDeltaTime);
    void Draw(SDL_Surface *pDest);
	int LevelEnd() { return mLevelEnd; }



	void LoadEnemies(std::list<Enemy*>& rList);
protected:
	std::list<Enemy*> enemy_cache;
	Layer* mpEnd;
	Layer* mpTop;
	int mLevelEnd;
	SDL_Surface* mpBackground;
	SDL_Surface* mpTopSurface;
	SDL_Rect mBounds;
};


#endif