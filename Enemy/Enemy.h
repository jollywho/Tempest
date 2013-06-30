#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Engine/Shared.h"

struct SpriteInfo;

class Enemy
{
protected:
	SpriteInfo* mpInfo;
    SDL_Rect mHitbox;
	std::string mId;
    SDL_Surface* mpCopySurface;
	static SDL_Color msHitColor;
	static SDL_Surface* mspHitSurface;

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
	float mX; 
	float mY;
	
	bool Explode(bool isDelete);
	bool CheckHealth();
	void DetectCollision();
public:
    explicit Enemy(int x, int y, int hp, std::string id);
	virtual ~Enemy() {};

    static void Init();
    static void Cleanup();

	virtual void Update(Uint32 deltaTicks) = 0;
    virtual void Draw(SDL_Surface *pDest) = 0;
	virtual void TakeHit(int dmg) = 0;

	void FlashRed(SDL_Surface* pSurface, SDL_Rect* pTargetClips);
    void FlashClear();
	bool CheckBounds();

    bool RequestDelete() { return mDelete; };
	bool IsExploding() { return mExplode; }
	bool IsAir() { return mAir; }
	bool IsHit() { return mHit; }
	SDL_Rect GetBounds() { return mHitbox; };
	
};
#endif