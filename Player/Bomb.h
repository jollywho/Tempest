#ifndef BOMB_B
#define BOMB_B

#include "Engine/Shared.h"

struct SpriteInfo;

class Bomb
{
public:
    Bomb();
    ~Bomb();
    void Update(const int& iElapsedTime);
	void Draw(SDL_Surface* dest);
    bool IsActive() { return active; };
	void Start(int x, int y);
private:
    Timer dps_timer;
	Timer clip_timer;
	bool active;
	static SpriteInfo* sprite;
	int clip;
	int xVal; int yVal;

};

#endif