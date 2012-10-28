#pragma once
#ifndef SCORESTATE_H
#define SCORESTATE_H

#include "Gamestate.h"
#include <sstream>

struct SpriteInfo;
class NFont;

class ScoreBanner
{
public:
	ScoreBanner(){};
	int x; int y;
	int scoreX()	{ return x + 225; }
	int scoreY()	{ return y + 48; }

	int rankX()		{ return x + 120; }
	int rankY()		{ return y + 85; }
	int nameX()		{ return x + 225; }
	int nameY()		{ return y + 85; }
	int stageX()	{ return x + 335; }
	int stageY()	{ return y + 85; }
};

class CScoreState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause(){}
	void Resume(){}
	void Return(){}

	void CheckKeys(const KeyStruct& keys);
	void Update(const int& iElapsedTime);
	void Draw(SDL_Surface* dest);

	static CScoreState* Instance() {
		return &m_SelectState;
	}
protected:
	CScoreState() { }

private:
	static CScoreState m_SelectState;
	void DrawMsg(int centerX, int centerY, int value);
	void DrawMsg(int centerX, int centerY, std::string msg);
	int modeSelection;
	NFont* font;
	NFont* score_font;
	SDL_Surface* font_surface;
	SDL_Surface* score_font_surface;
	SDL_Surface* banner;
	int selChange;
	float mov; int middle; int right;
	bool exit; bool enter;
	int dir;
	ScoreBanner bannerList[4];
	Timer mov_timer;
};

#endif