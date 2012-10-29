#ifndef BOMBUP_H
#define BOMBUP_H

#include "Item.h"

class Bombup : public Item
{
private:
	SpriteInfo* mpPickup;
public:
	Bombup(int x, int y, int value);
    ~Bombup();
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *pDest);
};


#endif

