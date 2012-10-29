#ifndef QUARTZ_H
#define QUARTZ_H

#include "Item.h"

class Quartz : public Item
{
private:
	Timer mAccelTimer;
	bool mLockedOn;
public:
	Quartz(int x, int y, int value);
    ~Quartz();
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *pDest);
};


#endif

