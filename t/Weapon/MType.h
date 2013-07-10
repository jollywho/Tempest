#ifndef MTYPE_H
#define MTYPE_H

#include "Weapon.h"

struct SpriteInfo;

class MType : public Weapon 
{
public:
	MType();
	~MType();
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface *pDest);
	void MajorAttack(std::list<PlayerBullet*>& pl_bulletlist);
	void MinorAttack(std::list<PlayerBullet*>& pl_bulletlist);
	void SetPos(int x, int y, int mv);
	void ResetPos(int x, int y);
	void StopAttack();
	void Shift();
	void Unshift();
private:
	SpriteInfo* mpShotAnim;
	int mShotAnimClip;
	Timer mShotAnimTimer;
	float mov;
	Point wpn_pos;
};

#endif