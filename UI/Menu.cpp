#include "Menu.h"
#include "MenuItem.h"
#include "Engine/Shared.h"
#include "Engine/SpriteResource.h"

Menu::Menu()
{
	printf("Menu Create\n");
    maxItems = 0;
    selectedindex = 1;
	SpriteResource::AddResource("UI", "selector.png", 155, 60, 60, 3, true);
	info = &SpriteResource::RequestResource("UI", "selector.png");
	font = TTF_OpenFont("Font/plantc.ttf", 24);
	clip = 0;
	click = false;
	clip_timer.start();
}

Menu::~Menu()
{
    printf("Menu Delete\n");
    for (auto it = menuList.begin(); it != menuList.end(); it++)
    {
        delete (*it);
    }
	TTF_CloseFont(font);
    menuList.clear();
}

void Menu::AddItem(int x, int y, char* msg)
{
	maxItems++;
	menuList.push_back(new MenuItem(maxItems, x, y, msg, font));
}

void Menu::Update(Uint32 deltaTicks, int alpha)
{
	if (click)
		Shared::CheckClip(clip_timer, clip, info->interval, info->clip_count, info->clip_count-1);
    SDL_SetAlpha(info->surface, SDL_SRCALPHA, alpha);
    for (auto it = menuList.begin(); it != menuList.end(); it++)
    {
        (*it)->Update(deltaTicks, alpha, selectedindex);
        if ((*it)->index == selectedindex)
            MoveSelector(&(*it)->GetBounds());
    }
}

void Menu::MoveSelector(SDL_Rect* bounds)
{
    selectorOffset.x = (bounds->x + bounds->w/2) - info->width/2;
    selectorOffset.y = (bounds->y + bounds->h/2) - info->height/2;
}

void Menu::Draw(SDL_Surface *dest)
{
    for (auto it = menuList.begin(); it != menuList.end(); it++)
    {
        (*it)->Draw(dest);
    }
    SDL_BlitSurface(info->surface, &info->clips[clip], dest, &selectorOffset);
}

void Menu::Reset()
{
	click = false;
	clip = 0;
	selectedindex = 1;
}

void Menu::Select()
{
	click = true;
}

void Menu::SetIndex(int direction)
{
	if (!click)
	{
		selectedindex += direction;
		if (selectedindex < 1) selectedindex = maxItems;
		if (selectedindex > maxItems) selectedindex = 1;
	}
}

Point Menu::GetFontSize(char* msg)
{
	int w; int h;
	TTF_SizeText(font, msg, &w, &h);
	return Point(w,h);
}