#ifndef LEVEL01_H
#define LEVEL01_H
#include "Level.h"

class Level01 : public Level
{
public:
    Level01();
    ~Level01();
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface *pDest);
	void LoadEnemies(std::list<Enemy*>& rList);
};

#endif