#ifndef LAYER_H
#define LAYER_H

#include "Engine/Shared.h"

class Layer
{
public:
    Layer(SDL_Surface* src, int height, int startPos);
	Layer(SDL_Surface* src, int height, int startPos, int xoffset);
    ~Layer();
    void Draw(SDL_Surface *pDest);
	void Update(Uint32 deltaTicks, float spd);
	void Start();
	bool IsDone() { return mDone; }
private:
	SDL_Rect mBounds;
    SDL_Surface* mpSurface;
	float mY; float mY2;
	int mStartY;
	int mHeight; int mOffset;
	bool mFixed; 
	bool mDone; 
	bool mStarted;
};

#endif