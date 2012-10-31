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

private:
	/* Fonts */
	NFont* mpRedFont;
	SDL_Surface* mpRedSurface;

	/* Message Points */
	Point mScore;
	Point mHiScore;
	int mGemOrigin;
	Point mGem;
	Point mCoin;
	//gem
	//star

	/* Messages */
    std::stringstream mScoreStr;
	std::stringstream mHiScoreStr;
    std::stringstream mBulletCountStr;
	std::stringstream mGemCountStr;
	std::stringstream mCoinCountStr;

	/* Healthbar */
	static const int MAX_BAR_WIDTH = 475;
	SpriteInfo* mpHpBar;
	bool mHpBarActive;
	Point mHpBar;
    Timer mHpBarTimer;
	double mHpBarTarget;

	/* Boss Warning */
	Point mWarningLeft;
	Point mWarningRight;
	SDL_Surface* mpWarningLeftSurface;
	SDL_Surface* mpWarningRightSurface;

	/* Banner */
	SDL_Surface* mpBannerLeftSurface;
	SDL_Surface* mpBannerRightSurface;

    /* Icons */
	NSprite* mpLives[5]; //todo: change to constant in gamescores
	NSprite* mpBombs[5];
	NSprite* mpMode;
	NSprite* mpPlayer;
	NSprite* mpHigh;
	Point mBannerBot;
	SDL_Surface* mpBannerBotSurface;
	SDL_Surface* mpBannerBot2Surface;
};
#endif