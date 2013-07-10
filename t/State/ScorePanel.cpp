#include "scorepanel.h"
#include <sstream>
#include "Engine/NFont.h"
#include "Engine/SpriteResource.h"
#include "UI/NSprite.h"
#include "Game/SaveScore.h"
#include "Game/GameScore.h"

ScorePanel::ScorePanel()
{
	printf("-ScorePanel Created-\n");
	mBack = false; mForward = false;

	mpMode = new NSprite(GAME_UI_MODE_X, GAME_UI_MODE_Y, &SpriteResource::RequestResource("UI", "mode_normal"), false, true);
	banner = Shared::LoadImage("Image/UI/ScoreBanner.png");
	mpTitle = Shared::LoadImage("Image/UI/highscore_title.png");
	score_font_surface = Shared::LoadImage("Font/BlueHigh.png");
	score_font = new NFont(SDL_GetVideoSurface(), score_font_surface);
	modeSelection = 1; selChange = 0;
	right = WINDOW_WIDTH + 50;
	exit = false; enter = true; mov = right;
	
	middle = WINDOW_WIDTH/2 - 451/2;
	int spacer = WINDOW_HEIGHT/2 - (113*4)/2;
	dir = -20;
	for (int i=0; i<=4; i++)
	{
		bannerList[i].x = right;
		bannerList[i].y = spacer + (i * 113);
	}
	mov_timer.Start();
}

ScorePanel::~ScorePanel()
{
	printf("-ScorePanel Deleted-\n");
	SDL_EnableKeyRepeat(0, 0);
	SDL_FreeSurface(score_font_surface);
	SDL_FreeSurface(banner);
	SDL_FreeSurface(mpTitle);
	delete score_font;
	delete mpMode;
}

void ScorePanel::KeyInput(const KeyStruct& rKeys)
{
	if (rKeys.left)
	{
		exit = true; 
		selChange = -1;
		dir = -20;
		if (modeSelection - 1 < 1) selChange = +2;
		if (modeSelection - 1 > 3) selChange = -2;	
	}
	if (rKeys.right)
	{
		exit = true;
		selChange = 1;
		dir = 20;
		if (modeSelection + 1 < 1) selChange = +2;
		if (modeSelection + 1 > 3) selChange = -2;
	}
	if (rKeys.x)
		mBack = true;
}

void ScorePanel::Update(const int& rDeltaTime) 
{
	mpMode->Update();
	if (exit)
	{
		if (mov_timer.GetTicks() > 10)
		{
			mov += dir;
			mov_timer.Start();
		}
		if ((dir < 0 && mov < -451) || (dir > 0 && mov > WINDOW_WIDTH) ) 
		{
			if (dir > 0) mov = -451;
			if (dir < 0) mov = WINDOW_WIDTH + 50;
			modeSelection += selChange;
			selChange = 0;
			exit = false; enter = true;
		}
		for (int i=0; i<5; i++)
			bannerList[i].x = mov;
	}
	if (enter)
	{
		if (mov_timer.GetTicks() > 10)
		{
			mov += dir;
			mov_timer.Start();
		}
		if ((dir > 0 && mov > WINDOW_WIDTH/2 - 451/2) || (dir < 0 && mov < WINDOW_WIDTH/2 - 451/2))
		{
			enter = false;
			mov = middle;

			delete mpMode;
			mpMode = new NSprite(GAME_UI_MODE_X, GAME_UI_MODE_Y, 
					&SpriteResource::RequestResource("UI", GameScore::GetModeEquivalent(modeSelection, true) + ".png"), false, true);

		}
		for (int i=0; i<5; i++)
			bannerList[i].x = mov;
	}
}

void ScorePanel::Draw(SDL_Surface* pDest) 
{
	for (int i=0; i<4; i++)
	{
		Shared::DrawSurface(bannerList[i].x, bannerList[i].y, banner, pDest);
		ScoreIO::ScoreData temp = ScoreIO::SaveScore::GetScores(GameScore::GetModeEquivalent(modeSelection), i+1);
		DrawMsg(bannerList[i].scoreX(), bannerList[i].scoreY(), temp.value);
		DrawMsg(bannerList[i].rankX(), bannerList[i].rankY(), temp.rank);
		DrawMsg(bannerList[i].nameX(), bannerList[i].nameY(), temp.name);
		DrawMsg(bannerList[i].stageX(), bannerList[i].stageY(), temp.stage);
	}
}

void ScorePanel::DrawTop(SDL_Surface* pDest)
{
	Shared::DrawSurface(0,1, mpTitle, pDest);

	if (!enter && !exit)
		mpMode->Draw(pDest);
}

void ScorePanel::DrawMsg(int centerX, int centerY, int value)
{
	int width = 0; int height = 0;
	std::stringstream msg;
	msg << value;
	width = score_font->getWidth(msg.str().c_str());
	height = score_font->getHeight(msg.str().c_str());
	score_font->draw(centerX - width/2, centerY - height/2, msg.str().c_str());
}

void ScorePanel::DrawMsg(int centerX, int centerY, std::string msg)
{
	int width = 0; int height = 0;
	width = score_font->getWidth(msg.c_str());
	height = score_font->getHeight(msg.c_str());
	score_font->draw(centerX - width/2, centerY - height/2, msg.c_str());
}