#ifndef BOMB_H
#define BOMB_H

#include "Item.h"

class Bomb : public Item
{
private:
	SpriteInfo* _received;
public:
	Bomb(int x, int y, int value);
    ~Bomb();
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *dest);
};


#endif

