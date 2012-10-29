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


	/* Messages */
	Point score_title_pos;
	Point hiscore_title_pos;
	Point mode_title_pos;
	Point score_pos;
	Point hiscore_pos;
	int score_origin;
	int gem_origin;
	Point gem_pos;
	Point coin_pos;
	//gem
	//star

	std::string str_mode;
    std::stringstream str_score;
	std::stringstream str_hiscore;
    std::stringstream str_bulletCount;
	std::stringstream str_gemcount;
	std::stringstream str_coincount;

	/* Healthbar */
	static const int MAX_BAR_WIDTH = 475;
	SpriteInfo* hpbar;
	bool hpbar_active;
	Point hpbar_pos;
    Timer hpbar_timer;
	double hpbar_mY;
	

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
    void Update(const int& rDeltaTime);
    void Draw(SDL_Surface *pDest);

    void DrawHealthBar(SDL_Surface *pDest);
    void DrawIcons(SDL_Surface *pDest);
	void ActivateHub();
    void ActivateHealthBar();
	void ActivateWarning();
    void DeactiveHealthBar();
	void SetHealthbarRatio(float ratio);
    void UpdateHealthBar();
	void UpdateIcons();

};
#endif