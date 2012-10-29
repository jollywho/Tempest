#ifndef TOTEM_H
#define TOTEM_H

#include "Engine/Shared.h"

struct SpriteInfo;

class Totem
{
private:
	SpriteInfo* mpInner;
	SpriteInfo* mpOuter;

    int mClip;
    Timer mClipTimer;

	float mX; float mY;
	Point mShift;
	Point mUnshift;
	Point mTarget;

	bool mUnset;
	bool mPull;
public:
    Totem::Totem(int ux, int uy, int sx, int sy); //todo: extra parameter for color of totem
	Totem::~Totem();
    void Update( const int& rDeltaTime, int x, int y, bool isAnimated);
	void Draw(SDL_Surface* pDest);

    void PullTotems();
    void ReleaseTotems();

    float GetMiddle();
    float GetVertical();

	void ResetPos(int x, int y);
};

#endif