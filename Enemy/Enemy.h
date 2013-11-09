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
#ifndef ENEMY_H
#define ENEMY_H

#include "Engine/Shared.h"
#include <list>
#include "Level/Factory.h"

struct SpriteInfo;
class Action;

class Enemy
{
protected:
	SpriteInfo* mpInfo;
    SDL_Rect mHitbox;
	std::string mId;
    SDL_Surface* mpCopySurface;
	static SDL_Color msHitColor;
	static SDL_Surface* mspHitSurface;

	std::list<Action*> mActions;
	std::list<Action*>::iterator mDo;

	Timer mHitTimer;
	Timer mClipTimer;

    int mClip;
	int mHealth;
	int mMaxHealth;

	bool mBombupSpawn;
	bool mPowerupSpawn;
	bool mCausesWipe;
    bool mExplode;
	bool mDelete;
	bool mAir;
	bool mHit;
	Point mPos;
	Point mVel;
	
	bool Explode(bool isDelete);
	bool CheckHealth();
	void DetectCollision();
public:
    explicit Enemy(std::string id, int x, int y, std::list<Action*>& actions);
	~Enemy();

    static void Init();
    static void Cleanup();

	virtual void Update(Uint32 delta_ticks) = 0;
    virtual void Draw(SDL_Surface *pdest) = 0;
	virtual void TakeHit(int dmg) = 0;

	void Decide(Uint32 delta_ticks);
	void FlashRed(SDL_Surface* pSurface, SDL_Rect* pTargetClips);
    void FlashClear();
	bool CheckBounds();
	void Movement(const float& x, const float& y);

    bool RequestDelete() { return mDelete; };
	bool IsExploding() { return mExplode; }
	bool IsAir() { return mAir; }
	bool IsHit() { return mHit; }
	SDL_Rect GetBounds() { return mHitbox; };
	
};
#endif