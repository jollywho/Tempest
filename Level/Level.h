#ifndef LEVEL_H
#define LEVEL_H

#include <list>

class Layer;
class Enemy;

class Level
{
public:
	virtual ~Level(){};
    virtual void Update(const int& iElapsedTime) = 0;
    virtual void Draw(SDL_Surface *dest) = 0;
	int GetLevelEnd() { return levelend; }

	/* Create enemies used for this level */
	virtual void LoadEnemies(std::list<Enemy*>& lst) = 0;
	//DrawTopLayer
protected:
	Layer* end;
	Layer* top;
	int levelend;
	SDL_Surface* bg;
};


#endif