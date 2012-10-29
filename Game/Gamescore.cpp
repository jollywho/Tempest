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

std::string GameScore::GetMode(bool verbose)
{
	std::string prefix;
	switch(g_mode)
	{
	case Mode::Normal:
		prefix = "Normal";
		break;
	case Mode::Ultra:
		prefix = "Ultra";
		break;
	case Mode::Insane:
		prefix = "Insane";
		break;
	default:
		prefix = "Test";
		break;
	}
	prefix = verbose? prefix + " Mode" : prefix;
	if (verbose)
		std::transform(prefix.begin(), prefix.end(), prefix.begin(), ::toupper);
	return prefix;
}

std::string GameScore::GetModeEquivalent(int mode, bool verbose)
{
	std::string prefix;
	switch(mode)
	{
	case 1:
		prefix = "Normal";
		break;
	case 2:
		prefix = "Ultra";
		break;
	case 3:
		prefix = "Insane";
		break;
	default:
		prefix = "Test";
		break;
	}
	return verbose? (prefix + " Mode") : prefix;
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
	SFX::PlaySoundResource("tick.wav");
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
	prevBonus = 10000;
    g_score = 0;
	//todo: relink
	//CPlayState::m_Continue = false;
	//CPlayState::m_GameOver = false;
	//CPlayState::mExit = false;
}

void GameScore::ResetLevel()
{
	mGems = 230;
	mCoins = 990;
	mQuartz = 50;
	mBombs = 0;
	mLives = 0;
}

void GameScore::ResetSpawn()
{
	mBombs = MAX_BOMBS;
	g_lives = MAX_LIVES;
	g_bonus = 0;
}