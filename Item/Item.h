#ifndef ITEM_H
#define ITEM_H

#include "Engine/Shared.h"
#include "Engine/SFX.h"

struct SpriteInfo;

class Item
{
protected:
    int clip;
    SDL_Rect offset;
    Timer clip_Timer;
	Timer duration_Timer;
    float xVal; float yVal;
    float xVel; float yVel;
	bool pickedup; bool received;
    int val;
	SpriteInfo* _info;
	int spawnside;
	static SDL_Surface* received_frame;
public:
    Item(int x, int y, int value, char* id);
    virtual ~Item();
    static void Init();
    static void CleanUp();
    bool m_delete;
    bool RequestDelete() { return m_delete; };
	virtual void Update(Uint32 deltaTicks){};
	virtual void Draw(SDL_Surface *dest){};
    void Check_Collision();
	void Check_WallCollision(double w, double h);
	bool CheckOffscreen(double x, double y, double h);
	static void SetBonus(int val);
	bool Air;
};
#endif

