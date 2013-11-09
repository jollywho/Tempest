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
#ifndef PLAYER_H
#define PLAYER_H

#include "Engine/Shared.h"
#include "Weapon/Weapon.h"
#include "Bomb.h"

struct SpriteInfo;
class Bomb;
class NSprite;

struct Directional 
{
	int left, right, up, down;
	Directional() : left(0), right(0), up(0), down(0) {}
};

class Player 
{
public:
    Player();
    ~Player();
	void Spawn();
    void KeyInput(const SDL_Event& rEvent);
    void Update( const int& rDeltaTime);
    void Draw(SDL_Surface *pdest);
    HitBox& GetBounds();
    HitBox& GetOuterBounds();
	Point GetCenter();
	void TakeHit();
	void Knockback(float xv, float yv, int force);
	static void SetWeaponType(WeaponType type);
	bool IsExploding() { return mExplode; }
	bool IsBombActive();
	void WeaponLevelUp();
	Weapon* GetWpn() { return mspWpn; }
private:
	void HandleMovement(const int& rDeltaTime);
	void HandleAttacks(const int& rDeltaTime);
	void UpdateExploding(const int& rDeltaTime);
	void UpdateLocked(const int& rDeltaTime);
	static Weapon* mspWpn;
	static Bomb* mspBomb;
	float mSpeed;
    float mov;
	int mKForce;
	Directional mDir;
	bool mShift; bool mAttack; bool mSlash;
	bool mBomb; bool mDash; bool mDashReq;
    static const int SPEED_NORMAL = 400;
	static const int SPEED_RECOVERY = 220;
	static const int HITBOX_SIZE = 10;
	static const int ANGEL_SIZE = 64;
	static const int INVULN_DURATION = 3000;

	bool mExplode;
	bool mInvuln;
	bool mLocked;

	Timer mKnockbackTimer;
	Timer mInvulnTimer;
    float mX; float mY;
	float mKx; float mKy;

	NSprite* mpDash;
	NSprite* mpAngel;
	NSprite* mpBooster;
	NSprite* mpHitbox;
	NSprite* mpZone;
	NSprite* mpExplosion;
	NSprite* mpWings;
};

#endif