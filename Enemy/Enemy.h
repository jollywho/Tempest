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

    static SDL_Surface* explo_surface;
    static SDL_Surface* hit_surface;
    SDL_Surface* copy_surface;
	static SDL_Color hitColor;

	Timer hit_timer;
	Timer clip_timer;

    int clip;
	int health;

    bool exploding;
	bool m_delete;
	bool active;
	bool air;
	bool hit;
	float xVal; float yVal;

	bool CheckBounds(float x, float y, float h);
	bool Explode(bool del);
	bool MonitorHealth();
	void DetectCollisions();
public:
    explicit Enemy(float x, float y, int hp, std::string id);
	
    static void Init();
    static void CleanUp();

    bool RequestDelete() { return m_delete; };
    virtual ~Enemy() {};

    virtual void Update(Uint32 deltaTicks) = 0;
    virtual void Draw(SDL_Surface *dest) = 0;
    
    void FlashRed(SDL_Surface* en_surface, SDL_Rect* targetClip);
    void FlashClear();

	bool IsExploding() { return exploding; }
	bool IsActive() { return active; }
	bool IsAir() { return air; }
	bool IsHit() { return hit; }
	SDL_Rect GetBounds() { return hitbox; };
	virtual void TakeHit(int dmg) = 0;
};
#endif