#ifndef MENUITEM_H
#define MENUITEM_H

#include "SDL_ttf.h"
#include "Engine/Timer.h"

class MenuItem
{
private:
	TTF_Font* mpFont;
    SDL_Surface* mpOuterSurface;
    SDL_Surface* mpInnerSurface;
    SDL_Rect mOffset;
    Timer mClipTimer;
    bool selected;
    int prev;
    char* text;
public:
    int index;
    explicit MenuItem(int indx, int x, int y, char* msg, TTF_Font* Font);
    ~MenuItem();
    void Move(float x, float y);
    void Update(Uint32 deltaTicks, int mAlpha, int indx);
    void Draw(SDL_Surface *pDest);
    void DrawSurface( int x, int y, SDL_Surface* pSource, SDL_Surface* pDest, SDL_Rect* pClip );
    SDL_Rect GetBounds() { return mOffset; }
};



#endif