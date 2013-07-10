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
    text = &msg;
    TTF_SetFontOutline(mpFont, 1);
    mpOuterSurface = TTF_RenderText_Blended(mpFont, &msg, color);
    TTF_SetFontOutline(mpFont, 0);
    mpInnerSurface = TTF_RenderText_Blended(mpFont, &msg, color2);

	int w = 0; int h = 0;
	TTF_SizeText(mpFont, text, &w, &h);
	mOffset.w = w; mOffset.h = h;
	mOffset.x = x-w/2; mOffset.y = y-h/2;

    selected = false;
    index = indx; //static counter increment each time
    prev = 0;
    mClipTimer.Start();
}

void MenuItem::Update(Uint32 deltaTicks, int mAlpha, int indx)
{
    if (prev != indx)
    {
        prev = indx;
        if (index == indx)
        {
            SDL_FreeSurface(mpOuterSurface);
            SDL_FreeSurface(mpInnerSurface);
            TTF_SetFontOutline(mpFont, 1);
            mpOuterSurface = TTF_RenderText_Blended(mpFont, text, color);
            TTF_SetFontOutline(mpFont, 0);
            mpInnerSurface = TTF_RenderText_Blended(mpFont, text, selColor);
        }
        else
        {
            SDL_FreeSurface(mpOuterSurface);
            SDL_FreeSurface(mpInnerSurface);
            TTF_SetFontOutline(mpFont, 1);
            mpOuterSurface = TTF_RenderText_Blended(mpFont, text, color);
            TTF_SetFontOutline(mpFont, 0);
            mpInnerSurface = TTF_RenderText_Blended(mpFont, text, color2);
        }
    }

    SDL_SetAlpha(mpOuterSurface, SDL_SRCALPHA, mAlpha);
    SDL_SetAlpha(mpInnerSurface, SDL_SRCALPHA, mAlpha);
}

void MenuItem::Draw(SDL_Surface *pDest)
{
	Shared::DrawSurface(mOffset.x, mOffset.y, mpOuterSurface, pDest);
	Shared::DrawSurface(mOffset.x, mOffset.y, mpInnerSurface, pDest);
}