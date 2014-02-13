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
#include "Menu.h"
#include "MenuItem.h"
#include "Engine/Shared.h"
#include "Engine/SpriteResource.h"

Menu::Menu()
{
	printf("Menu Create\n");
    mMaxItems = 0;
    mSelectedindex = 1;
	mpInfo = &SpriteResource::RequestResource("UI", "selector");
	mpFont = TTF_OpenFont("Font/plantc.ttf", 24);
	mClip = 0;
	mClick = false;
	mClipTimer.Start();
}

Menu::~Menu()
{
    printf("Menu Delete\n");
    for (auto it = menuList.begin(); it != menuList.end(); it++)
    {
        delete (*it);
    }
	TTF_CloseFont(mpFont);
    menuList.clear();
}

void Menu::AddItem(int x, int y, char* msg)
{
	mMaxItems++;
	menuList.push_back(new MenuItem(mMaxItems, x, y, *msg, *mpFont));
}

void Menu::Update(Uint32 delta_ticks, int alpha)
{
	if (mClick)
		Shared::CheckClip(mClipTimer, mClip, mpInfo->interval, mpInfo->maxClips, mpInfo->maxClips-1);
    SDL_SetAlpha(mpInfo->pSurface, SDL_SRCALPHA, alpha);
    for (auto it = menuList.begin(); it != menuList.end(); it++)
    {
        (*it)->Update(delta_ticks, alpha, mSelectedindex);
        if ((*it)->Index() == mSelectedindex)
            MoveSelector((*it)->GetBounds());
    }
}

void Menu::MoveSelector(SDL_Rect& bounds)
{
    mSelector.x = (bounds.x + bounds.w / 2) - mpInfo->width / 2;
    mSelector.y = (bounds.y + bounds.h / 2) - mpInfo->height / 2;
}

void Menu::Draw(SDL_Surface *pdest)
{
    for (auto it = menuList.begin(); it != menuList.end(); it++)
    {
        (*it)->Draw(pdest);
    }
	Shared::DrawSurface(mSelector.x, mSelector.y, mpInfo->pSurface, pdest, &mpInfo->pClips[mClip]);	
}

void Menu::Reset()
{
	mClick = false;
	mClip = 0;
	mSelectedindex = 1;
}

void Menu::Select()
{
	mClick = true;
}

void Menu::SetIndex(int index)
{
	mSelectedindex = index;
}

void Menu::MoveIndex(int direction)
{
	if (!mClick)
	{
		mSelectedindex += direction;
		if (mSelectedindex < 1) mSelectedindex = mMaxItems;
		if (mSelectedindex > mMaxItems) mSelectedindex = 1;
	}
}

Point Menu::GetFontSize(char& msg)
{
	int w; int h;
	TTF_SizeText(mpFont, &msg, &w, &h);
	return Point(w,h);
}