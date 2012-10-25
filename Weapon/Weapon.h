#ifndef WEAPON_H
#define WEAPON_H

class Weapon 
{
private:
	Timer wpnTimer;
	int minorSpeed;
	int majorSpeed;
	bool swap;
	bool IsShift;
public:
	Weapon();
	~Weapon();
	static PlayerBullet::WeaponType wpn;
	static PlayerBullet::AmmoType ammo;
	static void Init();
    static void CleanUp();
	void Update(Uint32 deltaTicks);
	void Draw(SDL_Surface *dest);
	void MajorAttack();
	void MinorAttack();
	void StopAttack();
	void Shift();
	void Unshift();
};

#endif