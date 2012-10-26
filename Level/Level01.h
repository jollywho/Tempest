#ifndef LEVEL01_H
#define LEVEL01_H
#include "Level.h"

class Level01 : public Level
{
public:
    Level01();
    ~Level01();
	void Update(const int& iElapsedTime);
	void Draw(SDL_Surface *dest);
	void LoadEnemies(std::list<Enemy*>& lst);
private:
	SDL_Surface* top_surface;
	SDL_Rect bounds;
};

#endif