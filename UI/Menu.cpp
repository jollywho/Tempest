#include "Menu.h"
#include "MenuItem.h"
#include "Engine/Shared.h"
#include "Engine/SpriteResource.h"

Menu::Menu()
{
	printf("Menu Create\n");
    mMaxItems = 0;
    mSelectedindex = 1;
	mpInfo = &SpriteResource::RequestResource("UI", "selector.png");
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
	menuList.push_back(new MenuItem(mMaxItems, x, y, msg, mpFont));
}

void Menu::Update(Uint32 deltaTicks, int alpha)
{
	if (mClick)
		Shared::CheckClip(mClipTimer, mClip, mpInfo->interval, mpInfo->maxClips, mpInfo->maxClips-1);
    SDL_SetAlpha(mpInfo->pSurface, SDL_SRCALPHA, alpha);
    for (auto it = menuList.begin(); it != menuList.end(); it++)
    {
        (*it)->Update(deltaTicks, alpha, mSelectedindex);
        if ((*it)->index == mSelectedindex)
            MoveSelector(&(*it)->GetBounds());
    }
}

void Menu::MoveSelector(SDL_Rect* bounds)
{
    mSelector.x = (bounds->x + bounds->w/2) - mpInfo->width/2;
    mSelector.y = (bounds->y + bounds->h/2) - mpInfo->height/2;
}

void Menu::Draw(SDL_Surface *pDest)
{
    for (auto it = menuList.begin(); it != menuList.end(); it++)
    {
        (*it)->Draw(pDest);
    }
	Shared::DrawSurface(mSelector.x, mSelector.y, mpInfo->pSurface, pDest, &mpInfo->pClips[mClip]);	
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

Point Menu::GetFontSize(char* msg)
{
	int w; int h;
	TTF_SizeText(mpFont, msg, &w, &h);
	return Point(w,h);
}