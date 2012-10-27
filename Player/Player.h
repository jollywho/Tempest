#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Engine/Shared.h"
#include "Weapon/Weapon.h"

struct SpriteInfo;

class Player 
{
public:
    Player();
    ~Player();

    void CheckKeys(const KeyStruct& keys);
    void ReSpawn();

	void HandleMovement(const int& iElapsedTime);
	void HandleAttacks(const int& iElapsedTime);
    void Update( const int& iElapsedTime);

    void Draw(SDL_Surface *dest);

    SDL_Rect GetBounds();
    SDL_Rect GetOuterBounds();
	Point GetCenter();
	void TakeHit();

	static void SetWeaponType(WeaponType type);

	bool IsExploding() { return exploding; }
	void WeaponLevelUp();

private:
	static Weapon* wpn;
	int moveSpeed;
    float mov;
	int left, right, up, down;
	bool shift; bool attack; bool bomb;
    static const int SPEED_NORMAL = 350;
    static const int SPEED_SLOW = 180;

	bool exploding;

	Point booster_pos;
	Timer booster_timer;
    int booster_clip;

	Point hitbox_pos;
	Timer hitbox_timer;
    int hitbox_clip;

    Point zone_pos;
    Timer zone_timer;
    int zone_clip;

    float xVal; float yVal;
    Timer clip_timer;
	int clip;

	SpriteInfo* angel;
	SpriteInfo* booster;
	SpriteInfo* hitbox;
	SpriteInfo* zone;
};

#endif