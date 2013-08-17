#include "Title.h"
#include <sstream>

Title::Title(const char* title)
{
	mStart = true; mDone = false;
	for (int i=0; i<4; i++)
	{
		std::ostringstream ss;
		ss << "Font/GoldNoonFadeRev"<< i << ".png";
		mspSurfaceFade[i] = Shared::LoadImage(ss.str());
		mpFont[i].load(SDL_GetVideoSurface(), mspSurfaceFade[i]);
	}
	mLength = 0;
	mMaxLength = 0;
	for (int i=0; title[i] != '\0'; i++)
	{
		mChars[i].fade = 0;
		mChars[i].ch[0] = title[i];
		mChars[i].ch[1] = '\n';
		mMaxLength++;
	}
	mPos = Point(WINDOW_WIDTH - 50, GAME_UI_TOP);
	mTimer.Start();
}

Title::~Title()
{
	for (int i=0; i<3; i++)
		SDL_FreeSurface(mspSurfaceFade[i]);
}


void Title::Update(const int& rDeltaTime)
{
	if (mDone) return;
	if (mLength < mMaxLength) 
	{
		if (mTimer.GetTicks() > 90)
		{
			mLength++;
			for (int i=0; i < mLength+1; i++)
			{
				if (mChars[i].fade < 3)
				{
					mChars[i].fade++;
				}
			}
			if (mChars[mLength].ch[0] == '\n')
				mTimer.SetTicks(120);
			else
				mTimer.Start();
		}
	}
	else {
		if (!mFinTimer.IsStarted()) mFinTimer.Start();
		if (mFinTimer.GetTicks() > 800) mDone = true;
	}
}

void Title::Draw(SDL_Surface *pDest)
{
	if (mDone) return;
	for (int i=0; i < mLength; i++)
	{
		mpFont[mChars[i].fade].draw(mPos.x, mPos.y + (20 * i), mChars[i].ch);
	}
}