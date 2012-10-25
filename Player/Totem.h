#ifndef TOTEM_H
#define TOTEM_H

#include "Engine/Shared.h"

struct SpriteInfo;

class Totem
{
private:
	SpriteInfo* inner;
	SpriteInfo* outer;

    int clip;
    Timer clip_Timer;

	float xVal; float yVal;
	Point shift_pos;
	Point unshift_pos;
	Point dest;

	bool unset;
	bool pull;
public:
    Totem::Totem(int ux, int uy, int sx, int sy); //todo: extra parameter for color of totem
	Totem::~Totem();
    void Update( const int& iElapsedTime, int x, int y, bool animate);
	void Draw(SDL_Surface* dest);

    void PullTotems();
    void ReleaseTotems();

    float GetMiddle();
    float GetVertical();
};

#endif