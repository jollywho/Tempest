#pragma once
#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Engine/Shared.h"

struct SpriteInfo;

//this is a member of Boss and sends signals to the game Interface
//		when it activates/ deactivates.
//todo: NSprite explosion once on 0 hp event
//todo: NSprite effect on hp loss (burning right edge or sparkle)
class HealthBar
{
private:
	static const int MAX_BAR_WIDTH = 475;
	SpriteInfo* mpHpBar;
	bool mHpBarActive;
	Point mHpBar;
    Timer mHpBarTimer;
	double mHpBarTarget;
public:
    HealthBar();
    ~HealthBar();
    void Update(const int& rDeltaTime);
    void Draw(SDL_Surface *pDest);
};
#endif