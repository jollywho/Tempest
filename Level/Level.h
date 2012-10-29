#ifndef LEVEL_H
#define LEVEL_H

#include <list>

class Layer;
class Enemy;

class Level
{
public:
	virtual ~Level(){};
    virtual void Update(const int& rDeltaTime) = 0;
    virtual void Draw(SDL_Surface *pDest) = 0;
	int LevelEnd() { return mLevelEnd; }

	/* Create enemies used for this level */
	virtual void LoadEnemies(std::list<Enemy*>& rList) = 0;
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