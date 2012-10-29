#ifndef ITEM_H
#define ITEM_H

#include "Engine/Shared.h"
#include "Engine/SFX.h"

struct SpriteInfo;

class Item
{
public:
    Item(int x, int y, int value, char* id);
    virtual ~Item();
    static void Init();
    static void Cleanup();
    bool mDelete;
    bool RequestDelete() { return mDelete; };
	virtual void Update(Uint32 deltaTicks){};
	virtual void Draw(SDL_Surface *pDest){};
    void CheckCollision();
	void CheckWallCollision(double w, double h);
	bool CheckOffscreen(double x, double y, double h);
	static void SetBonus(int val);
	bool Air() { return mAir; }
protected:
    int mClip;
    SDL_Rect mOffset;
    Timer mClipTimer;
	Timer mDurationTimer;
    float mX; float mY;
    float xvel; float yvel;
	bool pickedup; bool received;
    int val;
	bool mAir;
	SpriteInfo* mpInfo;
	int mSpawnSide;
	static SDL_Surface* smpPickupFrameInfo;
};
#endif

