#ifndef QUARTZ_H
#define QUARTZ_H

#include "Item.h"

class Quartz : public Item
{
private:
	Timer accel_Timer;
	bool lockedOn;
public:
	Quartz(int x, int y, int value);
    ~Quartz();
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *dest);
};


#endif

