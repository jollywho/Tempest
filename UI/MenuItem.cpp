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
#include "MenuItem.h"
#include "Menu.h"
#include "Engine/Shared.h"
//#include "Interface.h"

SDL_Color color =   {49, 38, 32};
SDL_Color color2 =  {200, 160, 88};
SDL_Color selColor =  {231, 230, 226};

MenuItem::~MenuItem()
{
    printf("Menu item del\n");
    SDL_FreeSurface(mpOuterSurface);
    SDL_FreeSurface(mpInnerSurface);
}

MenuItem::MenuItem(int indx, int x, int y, char& msg, TTF_Font& font)
{
	mpFont = &font;
    mpText = &msg;
    TTF_SetFontOutline(mpFont, 1);
    mpOuterSurface = TTF_RenderText_Blended(mpFont, &msg, color);
    TTF_SetFontOutline(mpFont, 0);
    mpInnerSurface = TTF_RenderText_Blended(mpFont, &msg, color2);

	int w = 0; int h = 0;
	TTF_SizeText(mpFont, mpText, &w, &h);
	mOffset.w = w; mOffset.h = h;
	mOffset.x = x-w / 2; mOffset.y = y-h / 2;

    mSelected = false;
    mIndex = indx; //static counter increment each time
    mPrev = 0;
    mClipTimer.Start();
}

void MenuItem::Update(Uint32 delta_ticks, int mAlpha, int indx)
{
    if (mPrev != indx)
    {
        mPrev = indx;
        if (mIndex == indx)
        {
            SDL_FreeSurface(mpOuterSurface);
            SDL_FreeSurface(mpInnerSurface);
            TTF_SetFontOutline(mpFont, 1);
            mpOuterSurface = TTF_RenderText_Blended(mpFont, mpText, color);
            TTF_SetFontOutline(mpFont, 0);
            mpInnerSurface = TTF_RenderText_Blended(mpFont, mpText, selColor);
        }
        else
        {
            SDL_FreeSurface(mpOuterSurface);
            SDL_FreeSurface(mpInnerSurface);
            TTF_SetFontOutline(mpFont, 1);
            mpOuterSurface = TTF_RenderText_Blended(mpFont, mpText, color);
            TTF_SetFontOutline(mpFont, 0);
            mpInnerSurface = TTF_RenderText_Blended(mpFont, mpText, color2);
        }
    }

    SDL_SetAlpha(mpOuterSurface, SDL_SRCALPHA, mAlpha);
    SDL_SetAlpha(mpInnerSurface, SDL_SRCALPHA, mAlpha);
}

void MenuItem::Draw(SDL_Surface *pdest)
{
	Shared::DrawSurface(mOffset.x, mOffset.y, mpOuterSurface, pdest);
	Shared::DrawSurface(mOffset.x, mOffset.y, mpInnerSurface, pdest);
}