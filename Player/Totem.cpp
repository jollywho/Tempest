#include "Totem.h"
#include "Engine/SpriteResource.h"

Totem::Totem(int ux, int uy, int sx, int sy)
{
	inner = &SpriteResource::RequestResource("Player", "TotemInner.png");
	outer = &SpriteResource::RequestResource("Player", "Totem.png");

	shift_pos.x = sx - outer->width/2; shift_pos.y = sy - outer->height/2;
	unshift_pos.x = ux - outer->width/2; unshift_pos.y = uy - outer->height/2;

	clip = 0;
	clip_Timer.start();
	pull = false;
	unset = true;
}

Totem::~Totem()
{
	//cleanup
}

void Totem::ReleaseTotems()
{
	pull = false;
	dest = unshift_pos;
}

void Totem::PullTotems()
{
	pull = true;
	dest = shift_pos;
}

void Totem::Update(const int& iElapsedTime, int x, int y, bool animate)
{
	if (unset) { xVal = x; yVal = y; unset = false; }
	if (animate) Shared::CheckClip(clip_Timer, clip, inner->interval, inner->clip_count, 0);

	float dx = (dest.x) - (xVal) + x;
    float dy = (dest.y) - (yVal) + y;
	double Length = sqrt(pow(dx, 2) + pow(dy, 2));

	float spd = Length * 5;
	
	float xa = dx / Length;
	float ya = dy / Length;
	xVal += (xa * (spd * (iElapsedTime / 1000.f)));
	yVal += (ya * (spd * (iElapsedTime / 1000.f)));
	
}

void Totem::Draw(SDL_Surface *dest)
{
	Shared::apply_surface(xVal+15, yVal+5, inner->surface, dest, &inner->clips[clip]);
    Shared::apply_surface(xVal, yVal, outer->surface, dest);
}

float Totem::GetMiddle()
{
    return xVal + outer->width/2;
}

float Totem::GetVertical()
{
    return yVal;
}