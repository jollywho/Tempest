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
#ifndef GAMESCORE_H
#define GAMESCORE_H
#include <string>

class GameScore
{
public:
	void ResetGame();
	void ResetLevel();
	void ResetSpawn();
	void SetMode(int mode);
	void IncreaseScore(int value);
	void IncreaseBombups();
	bool DecreaseBombups();
	void DecreaseCounter(int decrement, int type);
	void IncreaseLives();
	void DecreaseLives();
	void DecreaseContinues();
	void IncreaseCoinCount();
	void IncreaseQuartzCount();
	void IncreaseGemCount();
	void IncreaseBonus() {mBonus++;}

	static GameScore* Instance() {return &g_GameScore;}
    static const int MAX_BOMBS = 6;
    static const int MAX_LIVES = 6;
	std::string GetModeString(bool fileFormat = false);
	static std::string GetModeEquivalent(int mode, bool fileFormat = false);

	int GetBombs() {return mBombs;}
	int GetQuartzCount() {return mQuartz;}
	int GetGemCount() {return mGems;}
	int GetCoinCount() {return mCoins;}
	int GetLives() {return mLives;}
	int GetContinues() {return mContinues;}
	unsigned long GetBonus() {return 1;}
	unsigned long long GetScore() {return mScore;}
private:

	enum Mode
	{
		NORMAL = 50,
		ULTRA = 100,
		INSANE = 200,
	};

	static GameScore g_GameScore;

	Mode mGMode;
    unsigned long long mScore;
	int mCoins;
	int mBombs;
	int mLives;
	int mQuartz;
	int mGems;
	
	unsigned long long mPrevBonus;
	int mContinues;
	unsigned long mBonus;
};


#endif

