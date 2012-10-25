#ifndef MENUITEM_H
#define MENUITEM_H

#include "SDL_ttf.h"
#include "Engine/Timer.h"

class MenuItem
{
private:
	TTF_Font* font;
    SDL_Surface* surface;
    SDL_Surface* inner_surface;
    SDL_Rect offset;
    Timer clip_Timer;
    bool selected;
    int prev;
    char* text;
public:
    int index;
    explicit MenuItem(int indx, int x, int y, char* msg, TTF_Font* Font);
    ~MenuItem();
    void Move(float x, float y);
    void Update(Uint32 deltaTicks, int alpha, int indx);
    void Draw(SDL_Surface *dest);
    void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );
    SDL_Rect GetBounds() { return offset; }
};



#endif