#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Engine/Shared.h"

struct SpriteInfo;

class Player 
{
public:
    Player();
    ~Player();

    void CheckKeys(const KeyStruct& keys);
    void ReSpawn();

	void HandleMovement(const int& iElapsedTime);
    void Update( const int& iElapsedTime);

    void Draw(SDL_Surface *dest);

    SDL_Rect GetBounds();
    SDL_Rect GetOuterBounds();
	void TakeHit();
private:
	int moveSpeed;
    float mov;
	int left, right, up, down;
	bool shift; bool attack;
    static const int SPEED_NORMAL = 700;
    static const int SPEED_SLOW = 400;
    static const int FRAME_SPEED_NORMAL = 200;
    static const int FRAME_SPEED_SLOW = 450;

	Point boost_pos;
	Timer boost_timer;
    int boost_clip;

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