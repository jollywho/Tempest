#ifndef TOTEM_H
#define TOTEM_H

#include "Engine/Shared.h"

struct SpriteInfo;
class NSprite;

class Totem
{
private:
	static const int MAX_WIDTH = 48;
	static const int MAX_HEALTH = 50;
	SpriteInfo* mpInner;
	SpriteInfo* mpOuter;
	NSprite*  mpFlash;
	SDL_Surface* mpFrame;
	SDL_Surface* mpHealth;
	SDL_Surface* mpWarning;
	int mHealth;
    int mClip;
    Timer mClipTimer;
	Timer mDetTimer;
	Timer mHealthTimer;
	static const int SPEED = 5;
	SDL_Rect mHealthBox;
	float mX; float mY;
	Point mShift;
	Point mUnshift;
	Point mTarget;

	bool mShowHealth;
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

	bool IsDisabled() { return mDisable; }

	void ResetPos(int x, int y);
	void TakeHit();
};

#endif