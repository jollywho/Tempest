#ifndef TOTEM_H
#define TOTEM_H

#include "Engine/Shared.h"

struct SpriteInfo;
class NSprite;

class Totem
{
private:
	SpriteInfo* mpInner;
	SpriteInfo* mpOuter;
	NSprite*  mpFlash;
	int mHealth;
    int mClip;
    Timer mClipTimer;
	Timer mDetTimer;
	static const int SPEED = 5;

	float mX; float mY;
	Point mShift;
	Point mUnshift;
	Point mTarget;

	bool mUnset;
	bool mPull;
	bool mDet;
	bool mDisable;
public:
    Totem::Totem(int ux, int uy, int sx, int sy); //todo: extra parameter for color of totem
	Totem::~Totem();
    void Update( const int& rDeltaTime, int x, int y, bool isAnimated);
	void Draw(SDL_Surface* pDest);

    void PullTotems();
    void ReleaseTotems();

    float GetMiddle();
    float GetVertical();
	SDL_Rect GetBounds();

	void ResetPos(int x, int y);
	void TakeHit();
};

#endif