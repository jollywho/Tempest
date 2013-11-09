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
#include "GameScore.h"
#include "State/Playstate.h"
#include <algorithm>
#include "Engine/SFX.h"

GameScore GameScore::g_GameScore;

void GameScore::IncreaseScore(int value)
{
    g_score += value;
	if (g_score > prevBonus)
	{
		prevBonus *= 20;
		IncreaseLives();
	}
}
void GameScore::IncreaseLives()
{
	if (g_lives < MAX_LIVES)
		g_lives++;
}

void GameScore::IncreaseBombups()
{
	if (mBombs < MAX_BOMBS) {
		mBombs++; }
	else
		IncreaseScore(5000);
}

bool GameScore::DecreaseBombups()
{
	if (mBombs > 0) {
		mBombs--;
		return true; 
	}
	else
		return false;
}

void GameScore::SetMode(int mode) 
{ 
	switch (mode)
	{
	case 1:
		g_mode = Mode::Normal;
		break;
	case 2:
		g_mode = Mode::Ultra;
		break;
	case 3:
		g_mode = Mode::Insane;
		break;
	}
}

std::string GameScore::GetModeString(bool fileFormat)
{
	std::string prefix;
	std::string suffix;
	switch(g_mode)
	{
	case Mode::Normal:
		prefix = "Normal";
		suffix = "normal";
		break;
	case Mode::Ultra:
		prefix = "Ultra";
		suffix = "ultra";
		break;
	case Mode::Insane:
		prefix = "Insane";
		suffix = "insane";
		break;
	default:
		suffix = "normal";
		break;
	}
	return fileFormat? prefix : "mode_" + suffix;
}

std::string GameScore::GetModeEquivalent(int mode, bool fileFormat)
{
	std::string prefix;
	std::string suffix;
	switch(mode)
	{
	case 1:
		prefix = "Normal";
		suffix = "normal";
		break;
	case 2:
		prefix = "Ultra";
		suffix = "ultra";
		break;
	case 3:
		prefix = "Insane";
		suffix = "insane";
		break;
	default:
		prefix = "Test";
		suffix = "normal";
		break;
	}
	return fileFormat? ("mode_" +  suffix) : prefix;
}

void GameScore::DecreaseLives()
{
	mLives++;
	if (g_lives > 0)
		g_lives--;

	//todo: relink
	//else if (g_continues > 0)
	//	CPlayState::m_Continue = true;
	//else
	//	CPlayState::m_GameOver = true;
}

void GameScore::DecreaseContinues()
{
	g_continues--;
	g_score = 0;
	mCoins = 0;
	mGems = 0;
	mQuartz = 0;
	ResetLevel();
	ResetSpawn();
	//todo: relink
	//CPlayState::m_Continue = false;
}

void GameScore::DecreaseCounter(int decrement, int counter)
{
	SFX::PlaySoundResource("tick");
	switch(counter)
	{
	case 1:
		mGems -= decrement;
		break;
	case 2:
		mCoins -= decrement;
		break;
	case 3:
		mQuartz -= decrement;
		break;
	}
	
}

void GameScore::IncreaseCoinCount() { if (mCoins < 9999) mCoins++; }
void GameScore::IncreaseQuartzCount() { mQuartz++; }
void GameScore::IncreaseGemCount() { mGems++; }

void GameScore::ResetGame()
{
	g_continues = 3;
	prevBonus = 1000;
    g_score = 500000;
	ResetLevel();
	ResetSpawn();
	//todo: relink
	//CPlayState::m_Continue = false;
	//CPlayState::m_GameOver = false;
	//CPlayState::mExit = false;
}

void GameScore::ResetLevel()
{
	mGems = 0;
	mCoins = 0;
	mQuartz = 0;
	mBombs = 0;
	mLives = 0;
}

void GameScore::ResetSpawn()
{
	mBombs = MAX_BOMBS;
	g_lives = MAX_LIVES;
	g_bonus = 0;
}