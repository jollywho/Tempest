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
	if (g_bombs < MAX_BOMBS) {
		g_bombs++; t_bomb++; }
	else
		IncreaseScore(5000);
}

bool GameScore::DecreaseBombups()
{
	if (g_bombs > 0) {
		g_bombs--;
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
	t_lives++;
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
	t_coin = 0;
	t_gem = 0;
	t_quartz = 0;
	ResetLevel();
	ResetSpawn();
	//todo: relink
	//CPlayState::m_Continue = false;
}

void GameScore::DecreaseCounter(int val, int counter)
{
	SFX::PlaySoundResource("tick.wav");
	switch(counter)
	{
	case 1:
		t_gem -= val;
		break;
	case 2:
		t_coin -= val;
		break;
	case 3:
		t_quartz -= val;
		break;
	}
	
}

void GameScore::IncreaseCoinCount() { if (t_coin < 9999) t_coin++; }
void GameScore::IncreaseQuartzCount() { t_quartz++; }
void GameScore::IncreaseGemCount() { t_gem++; }

void GameScore::ResetGame()
{
	g_continues = 3;
	prevBonus = 10000;
    g_score = 0;
	//todo: relink
	//CPlayState::m_Continue = false;
	//CPlayState::m_GameOver = false;
	//CPlayState::m_Exit = false;
}

void GameScore::ResetLevel()
{
	t_gem = 0;
	t_coin = 0;
	t_bomb = 0;
	t_lives = 0;
	t_quartz = 0;
}

void GameScore::ResetSpawn()
{
	g_bombs = MAX_BOMBS;
	g_lives = MAX_LIVES;
	g_bonus = 0;
}