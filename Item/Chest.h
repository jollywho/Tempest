#ifndef CHEST_H
#define CHEST_H

#include "Item.h"

class Chest : public Item
{
private:
	int spawnCount;
	Timer spawn_Timer;
	bool opened;
public:
	Chest(int x, int y, int value);
    ~Chest();
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *dest);
};


#endif

