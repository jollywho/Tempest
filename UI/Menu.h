#ifndef MENU_H
#define MENU_H

#include "Engine/Shared.h"
#include "SDL_ttf.h"
#include <vector>

struct SpriteInfo;
class MenuItem;

class Menu
{
public:
    Menu();
    ~Menu();
    void AddItem(int x, int y, char* msg);
    void Update(Uint32 deltaTicks, int mAlpha);
    void Draw(SDL_Surface *pDest);
	void Reset();
	void Select();
	void MoveIndex(int direction);
	void Menu::SetIndex(int index);
	int GetIndex() { return mSelectedindex; }
	int Count() { return mMaxItems; }
	Point GetFontSize(char& msg);
private:
    std::vector<MenuItem*> menuList;
    int mMaxItems;
    Point mSelector;
	TTF_Font* mpFont;
	int mSelectedindex;
	SpriteInfo* mpInfo;
	Timer mClipTimer;
	int mClip;
	bool mClick;
	void MoveSelector(SDL_Rect& bounds);
};
 


#endif