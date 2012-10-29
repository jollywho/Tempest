#ifndef BOMB_B
#define BOMB_B

#include "Engine/Shared.h"

struct SpriteInfo;

class Bomb
{
public:
    Bomb();
    ~Bomb();
    void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* dest);
    bool IsActive() { return mActive; };
	void Start(int x, int y);
private:
    Timer dps_timer;
	Timer mClipTimer;
	bool mActive;
	static SpriteInfo* mpSprite;
	int mClip;
	int mX; int mY;

};

#endif