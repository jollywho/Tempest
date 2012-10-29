#pragma once
#ifndef SCOREMSG_H
#define SCOREMSG_H

#include <sstream>
#include "Engine/NFont.h"
#include "Engine/Shared.h"

class ScoreMSG
{
public:
    static void Init();
    static void Cleanup();
    ScoreMSG(int x, int y, int xDir, int value);
    ~ScoreMSG();    
    bool RequestDelete() { return mDelete; };
	
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *pDest);
private:
	static Timer msTallyTimer;
	static int msTallyTotal;
	static int msExtend;
    Timer mDurationTimer;
    float mX; float mY;
    float xvel; float yvel;
	int mValue;
	std::ostringstream mMsg;
	static SDL_Surface* mspSurfaceFade[4];
	static NFont msFontFade[4];
	int mClip;
	bool mDelete;
	Timer mClipTimer;
};


#endif

