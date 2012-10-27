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
	
	int GetBombs() { return g_bombs; }
	void IncreaseBombups();
	bool DecreaseBombups();

	void DecreaseCounter(int val, int type);

	int GetLives() { return g_lives; }
	void IncreaseLives();
	void DecreaseLives();

	int GetContinues() { return g_continues; }
	void DecreaseContinues();

	int GetCoinCount() { return t_coin; }
	void IncreaseCoinCount();

	int GetQuartzCount() { return t_quartz; }
	void IncreaseQuartzCount();

	int GetGemCount() { return t_gem; }
	void IncreaseGemCount();

	//unsigned long GetBonus() { return g_bonus; }
	unsigned long GetBonus() { return 1; }
	void IncreaseBonus() { g_bonus++; }

	std::string GetMode(bool verbose=false);
	static std::string GetModeEquivalent(int mode, bool verbose=false);
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

	int t_coin;
	int t_bomb;
	int t_lives;
	int t_quartz;
	int t_gem;
	
	unsigned long long prevBonus;
	int g_bombs;
	int g_lives;
	int g_continues;
	unsigned long g_bonus;
};


#endif

