#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Engine/Shared.h"
#include "Weapon/Weapon.h"
#include "Bomb.h"

struct SpriteInfo;
class Bomb;

class Player 
{
public:
    Player();
    ~Player();

    void KeyInput(const KeyStruct& rKeys);
    void ReSpawn();

	void HandleMovement(const int& rDeltaTime);
	void HandleAttacks(const int& rDeltaTime);
    void Update( const int& rDeltaTime);

    void Draw(SDL_Surface *pDest);

    SDL_Rect GetBounds();
    SDL_Rect GetOuterBounds();
	Point GetCenter();
	void TakeHit();

	static void SetWeaponType(WeaponType type);

	bool IsExploding() { return mExplode; }
	bool IsBombActive();
	void WeaponLevelUp();

private:
	static Weapon* mspWpn;
	static Bomb* mspBomb;
	int mSpeed;
    float mov;
	int left, right, up, down;
	bool mShift; bool mAttack; bool mBomb;
    static const int SPEED_NORMAL = 350;
    static const int SPEED_SLOW = 180;

	bool mExplode;

	Point mBooster;
	Timer mBoosterTimer;
    int mBoosterClip;

	Point mHitbox;
	Timer mHitboxTimer;
    int mHitboxClip;

    Point mZone;
    Timer mZoneTimer;
    int mZoneClip;

    float mX; float mY;
    Timer mClipTimer;
	int mClip;

	SpriteInfo* mpAngel;
	SpriteInfo* mpBooster;
	SpriteInfo* mpHitbox;
	SpriteInfo* mpZone;
};

#endif