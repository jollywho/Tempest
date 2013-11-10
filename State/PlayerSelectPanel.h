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
#ifndef PLAYERSELECTPANEL_H
#define PLAYERSELECTPANEL_H

#include "panel.h"
#include <list>
#include <sstream>

class NSprite;
class PlayerBullet;

class PlayerSelectPanel : public Panel
{
public:
    PlayerSelectPanel();
	~PlayerSelectPanel();

	void KeyInput(const SDL_Event& rEvent);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pdest);
	void DrawTop(SDL_Surface* pdest);
private:
	std::list<PlayerBullet*> mpBulletList;
	int mIndex;
	SDL_Surface* mpTitle;
	NSprite* mpPlayer;
};
 

#endif
