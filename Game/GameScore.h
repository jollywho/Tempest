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
	static GameScore* Instance() {
		return &g_GameScore;
	}
    static const int MAX_BOMBS = 6;
    static const int MAX_LIVES = 6;

	void ResetGame();
	void ResetLevel();
	void ResetSpawn();
	
	void IncreaseScore(int value);
	unsigned long long GetScore() { return g_score; }
	
	int GetBombs() { return mBombs; }
	void IncreaseBombups();
	bool DecreaseBombups();

	void DecreaseCounter(int decrement, int type);

	int GetLives() { return g_lives; }
	void IncreaseLives();
	void DecreaseLives();

	int GetContinues() { return g_continues; }
	void DecreaseContinues();

	int GetCoinCount() { return mCoins; }
	void IncreaseCoinCount();

	int GetQuartzCount() { return mQuartz; }
	void IncreaseQuartzCount();

	int GetGemCount() { return mGems; }
	void IncreaseGemCount();

	//unsigned long GetBonus() { return g_bonus; }
	unsigned long GetBonus() { return 1; }
	void IncreaseBonus() { g_bonus++; }

	std::string GetModeString(bool fileFormat=false);
	static std::string GetModeEquivalent(int mode, bool fileFormat=false);
	void SetMode(int mode);

private:
	enum Mode
	{
		Normal = 50,
		Ultra = 100,
		Insane = 200,
	};
	static GameScore g_GameScore;

	Mode g_mode;
    unsigned long long g_score;

	int mCoins;
	int mBombs;
	int mLives;
	int mQuartz;
	int mGems;
	
	unsigned long long prevBonus;
	int g_lives;
	int g_continues;
	unsigned long g_bonus;
};


#endif

