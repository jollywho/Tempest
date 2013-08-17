#pragma once
#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Engine/Shared.h"

struct SpriteInfo;
struct TextureInfo;
class NSprite;

//UI Object for displaying a % value with some fancy animation.
class HealthBar
{
private:
	int MAX_BAR_WIDTH;
	int MAX_VALUE;
	SpriteInfo* mpInfo;
	TextureInfo* mpBorder;
	NSprite* mpMarker;
	NSprite* mpExplosion;
	
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
public:
	//id_t: Texture border
	//id_s: Sprite bar
	//p:  Location
	//u_border: Enable drawing border
    explicit HealthBar(std::string id_t, std::string id_s, Point& p, bool draw_border);
    ~HealthBar();
    void Update();
    void Draw(SDL_Surface *pDest);
	void SetValue(int& val) { mVal = val; }
	void SetRecRate(int& val) { mRecRate = val; }
};
#endif