#include "scorestate.h"
#include "Engine/NFont.h"
#include "Engine/SpriteResource.h"
#include "Game/SaveScore.h"
#include "Game/GameScore.h"

CScoreState CScoreState::m_SelectState;

void CScoreState::Init()
{
	printf("CScoreState Init\n");
	ClearRequest();
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	SDL_Surface* temp = Shared::load_image("Image/UI/scores.bmp");
	bg = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	banner = Shared::load_image("Image/UI/ScoreBanner.png");
	font_surface = Shared::load_image("Font/GoldMistral.png");
	score_font_surface = Shared::load_image("Font/BlueHigh.png");
	font = new NFont(SDL_GetVideoSurface(), font_surface);
	score_font = new NFont(SDL_GetVideoSurface(), score_font_surface);
	modeSelection = 1; selChange = 0;
	right = _WSCREEN_WIDTH + 50;
	exit = false; enter = true; mov = right;
	middle = _WSCREEN_WIDTH/2 - 451/2;
	int spacer = _WSCREEN_HEIGHT/2 - (113*5)/2;
	for (int i=0; i<=5; i++)
	{
		bannerList[i].x = right;
		bannerList[i].y = spacer + (i * 113);
	}
	mov_timer.start();
}

void CScoreState::Cleanup()
{
	printf("CScoreState Cleanup\n");
	SDL_EnableKeyRepeat(0, 0);
	SDL_FreeSurface(bg);
	SDL_FreeSurface(font_surface);
	SDL_FreeSurface(score_font_surface);
	SDL_FreeSurface(banner);
	delete font;
	delete score_font;
}

void CScoreState::CheckKeys(const KeyStruct& keys)
{
	if (keys.left)
	{
		exit = true; 
		selChange = -1;
		if (modeSelection - 1 < 1) selChange = +2;
		if (modeSelection - 1 > 3) selChange = -2;	
	}
	if (keys.right)
	{
		exit = true;
		selChange = 1;
		if (modeSelection + 1 < 1) selChange = +2;
		if (modeSelection + 1 > 3) selChange = -2;
	}
	if (keys.z)
		PopMenu();
}

void CScoreState::Update(const int& iElapsedTime) 
{
	if (exit)
	{
		if (mov_timer.get_ticks() > 10)
		{
			mov += 10;
			mov_timer.start();
		}
		for (int i=0; i<5; i++)
			bannerList[i].x = mov;
		if (mov > right) 
		{
			modeSelection += selChange;
			selChange = 0;
			exit = false; enter = true;
		}
	}
	if (enter)
	{
		if (mov_timer.get_ticks() > 10)
		{
			mov -= 10;
			mov_timer.start();
		}
		for (int i=0; i<5; i++)
			bannerList[i].x = mov;
		if (mov < middle)
			enter = false;
	}
}

void CScoreState::Draw(SDL_Surface* dest) 
{
	//SDL_BlitSurface(bg, NULL, dest, NULL);
	for (int i=0; i<5; i++)
	{
		Shared::apply_surface(bannerList[i].x, bannerList[i].y, banner, dest);
		ScoreIO::ScoreData temp = ScoreIO::SaveScore::GetScores(GameScore::GetModeEquivalent(modeSelection), i+1);
		DrawMsg(bannerList[i].scoreX(), bannerList[i].scoreY(), temp.value);
		DrawMsg(bannerList[i].rankX(), bannerList[i].rankY(), temp.rank);
		DrawMsg(bannerList[i].nameX(), bannerList[i].nameY(), temp.name);
		DrawMsg(bannerList[i].stageX(), bannerList[i].stageY(), temp.stage);
	}
	font->draw(0, 0, GameScore::GetModeEquivalent(modeSelection + selChange, true).c_str());
	SDL_UpdateRect(dest, 0, 0, 0, 0);
}

void CScoreState::DrawMsg(int centerX, int centerY, int value)
{
	int width = 0; int height = 0;
	std::stringstream msg;
	msg << value;
	width = score_font->getWidth(msg.str().c_str());
	height = score_font->getHeight(msg.str().c_str());
	score_font->draw(centerX - width/2, centerY - height/2, msg.str().c_str());
}

void CScoreState::DrawMsg(int centerX, int centerY, std::string msg)
{
	int width = 0; int height = 0;
	width = score_font->getWidth(msg.c_str());
	height = score_font->getHeight(msg.c_str());
	score_font->draw(centerX - width/2, centerY - height/2, msg.c_str());
}