#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Engine/Shared.h"

struct SpriteInfo;

class Enemy
{
protected:
	SpriteInfo* info;

    SDL_Rect hitbox;

    static SDL_Surface* hit_surface;
    SDL_Surface* copy_surface;
	static SDL_Color hitColor;

	Timer hit_timer;
	Timer clip_timer;

    int clip;
	int health;
	int max_health;

	bool bullet_wipe;
    bool exploding;
	bool m_delete;
	bool air;
	bool hit;
	float xVal; float yVal;

	
	bool Explode(bool del);
	bool CheckHealth();
	void DetectCollision();
public:
    explicit Enemy(int x, int y, int hp, std::string id);
	virtual ~Enemy() {};

    static void Init();
    static void CleanUp();

    bool RequestDelete() { return m_delete; };
    

    virtual void Update(Uint32 deltaTicks) = 0;
    virtual void Draw(SDL_Surface *dest) = 0;
    
    void FlashRed(SDL_Surface* en_surface, SDL_Rect* targetClip);
    void FlashClear();

	bool CheckBounds();
	bool IsExploding() { return exploding; }
	bool IsAir() { return air; }
	bool IsHit() { return hit; }
	SDL_Rect GetBounds() { return hitbox; };
	virtual void TakeHit(int dmg) = 0;
};
#endif