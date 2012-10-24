#ifndef MENU_H
#define MENU_H

#include "SDL_ttf.h"
#include "MenuItem.h"
#include <vector>

class Menu
{
private:
    std::vector<MenuItem*> menuList;
    bool submenu;
    int maxItems;
    SDL_Rect selectorOffset;
	TTF_Font* font;
	int selectedIndex;
public:
    Menu();
    ~Menu();
    void AddItem(int x, int y, char* msg);
    void Update(Uint32 deltaTicks, int alpha);
    void Draw(SDL_Surface *dest);
    void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );
    void MoveSelector(SDL_Rect* bounds);
    static SDL_Surface* selector;
	void SetIndex(int direction);
};
 


#endif