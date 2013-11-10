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
#ifndef SCORESTATE_H
#define SCORESTATE_H

#include "panel.h"

class NFont;
class NSprite;

class ScoreBanner
{
public:
	ScoreBanner(){};
	int x; int y;
	int scoreX()	{return x + 225;}
	int scoreY()	{return y + 48;}
	int rankX()		{return x + 120;}
	int rankY()		{return y + 85;}
	int nameX()		{return x + 225;}
	int nameY()		{return y + 85;}
	int stageX()	{return x + 335;}
	int stageY()	{return y + 85;}
};

class ScorePanel : public Panel
{
public:
	ScorePanel();
	~ScorePanel();
	void KeyInput(const SDL_Event& rEvent);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pdest);
	void DrawTop(SDL_Surface* pdest);
private:
	void DrawMsg(int centerX, int centerY, int value);
	void DrawMsg(int centerX, int centerY, std::string msg);
	int modeSelection;
	NFont* score_font;
	NSprite* mpMode;
	SDL_Surface* score_font_surface;
	SDL_Surface* banner;
	SDL_Surface* mpTitle;
	int selChange;
	float mov; int middle; int right;
	bool exit; bool enter;
	int dir;
	ScoreBanner bannerList[4];
	Timer mov_timer;
};

#endif