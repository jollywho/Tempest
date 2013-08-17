#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include "Engine/NFont.h"
#include "Engine/Shared.h"
#include "Game/Gamescore.h"

struct SpriteInfo;
struct FontInfo;
struct TextureInfo;
class NSprite;
class Inventory;
class Title;
class HealthBar;

class Interface
{
private:
	/* Fonts */
	FontInfo* mpRedFont;

	Title* mpTitle;
	Inventory* mpInv;

	/* Message Points */
	int mGemOrigin;
	Point mScore;
	Point mHiScore;
	Point mGem;
	Point mCoin;
	Point mUI;
	//gem
	//star
	
	/* Messages */
    char mScoreStr[30];
	char mHiScoreStr[30];
	char mGemStr[30];
	char mCoinStr[30];

    /* Icons */
	NSprite* mpMode;
	NSprite* mpPlayer;
	NSprite* mpHigh;

	HealthBar* mpManaLeft;
	HealthBar* mpManaRight;
	HealthBar* mpHealth;
	HealthBar* mpShield;
public:
    Interface();
    ~Interface();
    void Update(const int& rDeltaTime);
    void Draw(SDL_Surface *pDest);
    void DrawIcons(SDL_Surface *pDest);
	void ActivateHub();
	void UpdateIcons();
};
#endif