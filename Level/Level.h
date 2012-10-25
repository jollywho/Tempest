#ifndef LEVEL_H
#define LEVEL_H

class Layer;

class Level
{
public:
	virtual ~Level(){};
    virtual void Update(const int& iElapsedTime) = 0;
    virtual void Draw(SDL_Surface *dest) = 0;
	int GetLevelEnd() { return levelend; }
	//DrawTopLayer
protected:
	Layer* end;
	Layer* top;
	int levelend;
	SDL_Surface* bg;
};


#endif