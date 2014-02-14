/* Tempest - C++ Danmakufu Game for SDL
*
*  Copyright (C) 2013 Kevin Vollmer.
*  
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*  
ÅÅ*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
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
public:
    Interface();
    ~Interface();
    void Update(const int& rDeltaTime);
    void Draw(SDL_Surface *pdest);
    void DrawIcons(SDL_Surface *pdest);
	void ActivateHub();
	void UpdateIcons();

	void SetMana(int val);
	void SetHealth(int val);
	void SetShield(int val);
	void SetBomb(int val);

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

	HealthBar* mpManaleft;
	HealthBar* mpManaright;
	HealthBar* mpHealth;
	HealthBar* mpShield;
};

#endif