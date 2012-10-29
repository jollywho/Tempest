#ifndef POWERUP_H
#define POWERUP_H

#include "Item.h"

class Powerup : public Item
{
private:
	SpriteInfo* _received;
public:
	Powerup(int x, int y, int value);
    ~Powerup();
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *pDest);
};


#endif

