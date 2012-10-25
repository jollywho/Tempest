#ifndef LAYER_H
#define LAYER_H

#include "Engine/Shared.h"

class Layer
{
private:
	SDL_Rect bounds;
    SDL_Surface* surface;
	float yVal; float yVal2;
	int start;
	int height; int xoffset;
	bool fixed; bool done; bool started;
public:
    Layer(SDL_Surface* src, int height, int startPos);
	Layer(SDL_Surface* src, int height, int startPos, int xoffset);
    ~Layer();
    void Draw(SDL_Surface *dest);
	void Update(Uint32 deltaTicks, float spd);
	void Start();
	bool IsDone() { return done; }
};

#endif