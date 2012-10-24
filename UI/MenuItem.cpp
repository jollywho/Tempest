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
    SDL_FreeSurface(surface);
    SDL_FreeSurface(innerSurface);
}

MenuItem::MenuItem(int indx, int x, int y, char* msg, TTF_Font* Font)
{
	font = Font;
    text = msg;
    TTF_SetFontOutline(font, 1);
    surface = TTF_RenderText_Blended(font, msg, color);
    TTF_SetFontOutline(font, 0);
    innerSurface = TTF_RenderText_Blended(font, msg, color2);

    offset.x = x; offset.y = y;
	int w = 0; int h = 0;
	TTF_SizeText(font, text, &w, &h);
	offset.w = w; offset.h = h;
    selected = false;
    index = indx; //static counter increment each time
    prev = 0;
    clip_Timer.start();
}

void MenuItem::Update(Uint32 deltaTicks, int alpha, int indx)
{
    if (prev != indx)
    {
        prev = indx;
        if (index == indx)
        {
            SDL_FreeSurface(surface);
            SDL_FreeSurface(innerSurface);
            TTF_SetFontOutline(font, 1);
            surface = TTF_RenderText_Blended(font, text, color);
            TTF_SetFontOutline(font, 0);
            innerSurface = TTF_RenderText_Blended(font, text, selColor);
        }
        else
        {
            SDL_FreeSurface(surface);
            SDL_FreeSurface(innerSurface);
            TTF_SetFontOutline(font, 1);
            surface = TTF_RenderText_Blended(font, text, color);
            TTF_SetFontOutline(font, 0);
            innerSurface = TTF_RenderText_Blended(font, text, color2);
        }
    }

    SDL_SetAlpha(surface, SDL_SRCALPHA, alpha);
    SDL_SetAlpha(innerSurface, SDL_SRCALPHA, alpha);
}

void MenuItem::Draw(SDL_Surface *dest)
{
	Shared::apply_surface(offset.x, offset.y, surface, dest);
	Shared::apply_surface(offset.x, offset.y, innerSurface, dest);
}