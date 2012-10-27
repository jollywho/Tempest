#ifndef GEM_H
#define GEM_H

#include "Item.h"

class Gem : public Item
{
private:
	Timer accel_Timer;
	bool lockedOn;
public:
	Gem(int x, int y, int value, bool autolock=false);
    ~Gem();
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *dest);
};


#endif

