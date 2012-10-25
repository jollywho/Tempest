#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <sstream> 
#include "Engine/NFont.h"
#include "Engine/Shared.h"
#include "UI/NSprite.h"

struct SpriteInfo;
class NSprite;

class Interface
{
private:
	/* Fonts */
	NFont* font_red;
	NFont* font_green;
	SDL_Surface* green_surface;
	SDL_Surface* red_surface;

    std::stringstream str_score;
	std::stringstream str_hiscore;
    std::stringstream str_bulletCount;

	/* Healthbar */
	static const int MAX_BAR_WIDTH = 475;
	SpriteInfo* hpbar;
	bool hpbar_active;
	Point hpbar_pos;
    Timer hpbar_timer;
	double hpbar_yval;
	

	/* Boss Warning */
	Point warning_left;
	Point warning_right;
	SDL_Surface* warning_left_surface;
	SDL_Surface* warning_right_surface;

	/* Banner */
	SDL_Surface* banner_left_surface;
	SDL_Surface* banner_right_surface;

    /* Icons */
	NSprite* lives[5]; //todo: change to constant in gamescores
	NSprite* bombs[5];
	Point banner_bottom_pos;
	SDL_Surface* banner_bottom_surface;
	SDL_Surface* banner_bottom2_surface;
public:
    Interface();

    ~Interface();
    void Update(const int& iElapsedTime);
    void Draw(SDL_Surface *dest);

    void DrawHealthBar(SDL_Surface *dest);
    void DrawIcons(SDL_Surface *dest);
	void ActivateHub();
    void ActivateHealthBar();
	void ActivateWarning();
    void DeactiveHealthBar();
	void SetHealthbarRatio(float ratio);
    void UpdateHealthBar();
	void UpdateIcons();

};
#endif