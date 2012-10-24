#include "Menu.h"
#include "Engine/Shared.h"

SDL_Surface* Menu::selector;

Menu::Menu()
{
    maxItems = 0;
    selectedIndex = 1;
	selector = Shared::load_image("Image/UI/selector.png");
	font = TTF_OpenFont("Font/plantc.ttf", 24);
}

Menu::~Menu()
{
    printf("Menu del\n");
    for (auto it = menuList.begin(); it != menuList.end(); it++)
    {
        delete (*it);
    }
    menuList.clear();
}

void Menu::AddItem(int x, int y, char* msg)
{
	maxItems++;
	menuList.push_back(new MenuItem(maxItems, x, y, msg, font));
}

void Menu::Update(Uint32 deltaTicks, int alpha)
{
    SDL_SetAlpha(selector, SDL_SRCALPHA, alpha);
    for (auto it = menuList.begin(); it != menuList.end(); it++)
    {
        (*it)->Update(deltaTicks, alpha, selectedIndex);
        if ((*it)->index == selectedIndex)
            MoveSelector(&(*it)->GetBounds());
    }
}

void Menu::MoveSelector(SDL_Rect* bounds)
{
    selectorOffset.x = (bounds->x + bounds->w/2) - 240/2;
    selectorOffset.y = (bounds->y + 15) - 60/2;
}

void Menu::Draw(SDL_Surface *dest)
{
    for (auto it = menuList.begin(); it != menuList.end(); it++)
    {
        (*it)->Draw(dest);
    }
    SDL_BlitSurface(selector, NULL, dest, &selectorOffset);
}

void Menu::SetIndex(int direction)
{
	selectedIndex += direction;
	if (selectedIndex < 1) selectedIndex = maxItems;
    if (selectedIndex > maxItems) selectedIndex = 1;
}