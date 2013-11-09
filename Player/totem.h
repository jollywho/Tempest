/* Tempest - C++ Danmakufu Game for SDL
*
*  Copyright (C) 2013 Kevin Vollmer.
*  
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*  
ÅÅ*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
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
	void Draw(SDL_Surface* pdest);

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