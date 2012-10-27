#pragma once
#ifndef SCOREMSG_H
#define SCOREMSG_H

#include <sstream>
#include "Engine/NFont.h"
#include "Engine/Shared.h"

class ScoreMSG
{
private:
	static Timer tallyTimer;
	static int tallyTotal;
	static int extend;
    Timer duration_Timer;
    float xVal; float yVal;
    float xVel; float yVel;
	int val;
	std::ostringstream msg;
	static SDL_Surface* surfaceFade[4];
	static NFont fontFade[4];
	int clip;
	Timer clip_Timer;
public:
    static void Init();
    static void CleanUp();
    ScoreMSG(int x, int y, int xDir, int value);
    ~ScoreMSG();    
    bool RequestDelete() { return m_delete; };
	bool m_delete;

    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *dest);
};


#endif

