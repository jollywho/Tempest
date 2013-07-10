#ifndef PANEL_H
#define PANEL_H

#include "Engine/Shared.h"

/*
Common panel interface base class
*/
class Panel
{
public:
	virtual ~Panel() {}
	virtual void KeyInput(const KeyStruct& rKeys) = 0;
	virtual void Update(const int& rDeltaTime) = 0;
	virtual void Draw(SDL_Surface* pDest) = 0;
	virtual void DrawTop(SDL_Surface* pDest) {}
	bool Back() { return mBack; }
	bool Forward() { return mForward; }
protected:
	bool mBack;		//close request
	bool mForward;	//forward state request
};

#endif 