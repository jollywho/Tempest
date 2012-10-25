#ifndef MTYPE_H
#define MTYPE_H

#include "Weapon.h"

class Totem;
struct SpriteInfo;

class MType : public Weapon 
{
public:
	MType();
	~MType();
	void Update(const int& iElapsedTime);
	void Draw(SDL_Surface *dest);
	void MajorAttack(std::list<PlayerBullet*>& pl_bulletlist);
	void MinorAttack(std::list<PlayerBullet*>& pl_bulletlist);
	void SetPos(int x, int y, int mv);
	void StopAttack();
	void Shift();
	void Unshift();
	Totem* totem_list[MAX_TOTEMS];
private:
	SpriteInfo* shotanim;
	int shotanim_clip;
	Timer shotanim_timer;
	float mov;
	Point wpn_pos;
};

#endif