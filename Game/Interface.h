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
	NFont* mpGreenFont;
	SDL_Surface* mpGreenSurface;
	SDL_Surface* mpRedSurface;

	/* Message Points */
	Point mScoreTitle;
	Point mHiScoreTitle;
	Point mModeTitle;
	Point mScore;
	Point mHiScore;
	int mScoreOrigin;
	int mGemOrigin;
	Point mGem;
	Point mCoin;
	//gem
	//star

	/* Messages */
	std::string mModeStr;
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
	Point mBannerBot;
	SDL_Surface* mpBannerBotSurface;
	SDL_Surface* mpBannerBot2Surface;
};
#endif