#ifndef WEAPON_H
#define WEAPON_H

#include "Engine/Shared.h"
#include "PlayerBullet.h"
#include <vector>
#include <list>

class Totem;

enum WeaponType
{
	M_type,
	S_type,
	R_type,
};

class Weapon 
{
public:
	virtual void Update(const int& rDeltaTime) = 0;
	virtual void Draw(SDL_Surface *pDest) = 0;
	virtual void MajorAttack(std::list<PlayerBullet*>& pl_bulletlist) = 0;
	virtual void MinorAttack(std::list<PlayerBullet*>& pl_bulletlist) = 0;
	virtual void StopAttack() = 0;
	virtual void Shift() = 0;
	virtual void Unshift() = 0;
	virtual void SetPos(int x, int y, int mv) = 0;
	virtual void ResetPos(int x, int y) = 0;
	inline void LevelUp() { if (level < MAX_TOTEMS) level++; }
	virtual bool TakeHit() = 0;
protected:
	Timer wpn_timer;
	int minor_speed;
	int major_speed;
	bool is_shift;
	int level;
	int mHealth;
	int rot_divs;
	std::vector<Totem*> totem_list;
};

#endif