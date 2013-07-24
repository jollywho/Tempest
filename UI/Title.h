#pragma once
#ifndef TITLE_H
#define TITLE_H

#include "Engine/Shared.h"
#include "Engine/NFont.h"

struct SpriteInfo;

//this is a member of Level base and should be called
//		at the start of a level and before a boss is spawned.
class Title
{
private:
	struct FadeChar
	{
		int fade;
		char ch[2];
	} mChars[50];
	int mLength;
	int mMaxLength;
	bool mStart;
	bool mDone;
	Point mPos;
	Timer mTimer;
	NFont mpFont[5];
	SDL_Surface* mspSurfaceFade[5];
public:
    Title(const char* title);
    ~Title();
	void Start() { mStart = true; mLength = 0; }
    void Update(const int& rDeltaTime);
    void Draw(SDL_Surface *pDest);
};

#endif