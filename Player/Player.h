#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Engine/Shared.h"
#include "Weapon/Weapon.h"
#include "Bomb.h"

struct SpriteInfo;
class Bomb;
class NSprite;

class Player 
{
public:
    Player();
    ~Player();
	void Spawn();

    void KeyInput(const KeyStruct& rKeys);

    void Update( const int& rDeltaTime);

    void Draw(SDL_Surface *pDest);

    Rect& GetBounds();
    Rect& GetOuterBounds();
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
	int mSpeed;
    float mov;
	int mKForce;
	int left, right, up, down;
	bool mShift; bool mAttack; bool mBomb;
    static const int SPEED_NORMAL = 400;
    static const int SPEED_SLOW = 200;
	static const int SPEED_RECOVERY = 220;
	static const int HITBOX_SIZE = 20;
	static const int ANGEL_SIZE = 64;
	static const int INVULN_DURATION = 3000;

	bool mExplode;
	bool mInvuln;
	bool mLocked;

	Timer mKnockbackTimer;
	Timer mInvulnTimer;
    float mX; float mY;
	float mKx; float mKy;

	NSprite* mpAngel;
	NSprite* mpBooster;
	NSprite* mpHitbox;
	NSprite* mpZone;
	NSprite* mpExplosion;
	NSprite* mpWings;
};

#endif