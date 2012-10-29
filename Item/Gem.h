#ifndef GEM_H
#define GEM_H

#include "Item.h"

class Gem : public Item
{
private:
	Timer mAccelTimer;
	bool mLockedOn;
public:
	Gem(int x, int y, int value, bool autoLocked=false);
    ~Gem();
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *pDest);
};


#endif

