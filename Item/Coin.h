#ifndef COIN_H
#define COIN_H

#include "Item.h"

class Coin : public Item
{
private:
	Timer mAccelTimer;
public:
	Coin(int x, int y, int value);
    ~Coin();
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *pDest);
};


#endif

