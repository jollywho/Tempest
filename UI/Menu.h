#ifndef MENU_H
#define MENU_H

#include "Engine/Shared.h"
#include "SDL_ttf.h"
#include <vector>

struct SpriteInfo;
class MenuItem;

class Menu
{
private:
    std::vector<MenuItem*> menuList;
    int maxItems;
    SDL_Rect selectorOffset;
	TTF_Font* font;
	int selectedindex;
	SpriteInfo* info;
	Timer clip_timer;
	int clip;
	bool click;
	void MoveSelector(SDL_Rect* bounds);
public:
    Menu();
    ~Menu();
    void AddItem(int x, int y, char* msg);
    void Update(Uint32 deltaTicks, int alpha);
    void Draw(SDL_Surface *dest);
	
	void Reset();
	void Select();

	void SetIndex(int direction);
	int GetIndex() { return selectedindex; }

	Point GetFontSize(char* msg);
};
 


#endif