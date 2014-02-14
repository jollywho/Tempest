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
#pragma once
#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Engine/Shared.h"

struct SpriteInfo;
struct TextureInfo;
class NSprite;

class HealthBar
{
public:
    explicit HealthBar(std::string id_t, std::string id_s, Point& p, bool draw_border, bool left_dir);
    ~HealthBar();
    void Update();
    void Draw(SDL_Surface *pdest);
	void SetValue(int& val) { mVal += val; }
	void SetRecRate(int& val) { mRecRate = val; }
	void SetMaxVal(int& val);
	int GetVal() { return mVal; }

private:
	int MAX_BAR_WIDTH;
	int MAX_VALUE;
	SpriteInfo* mpInfo;
	TextureInfo* mpBorder;
	NSprite* mpMarker;
	NSprite* mpExplosion;
	
	bool mLeftDir;
	bool mBorder;
	int mVal;
	int mClip;
	int mRecRate;
	int mDir;
	int mDrainDir;
	SDL_Rect mBarLevel;
	Point mPos;
    Timer mClipTimer;
	Timer mRecTimer;
	double mHpBarTarget;
};

#endif