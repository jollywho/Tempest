#pragma once
#ifndef NOISE_H
#define NOISE_H

#include "Action.h"

class Noise : public Action
{
private:
	bool mMusic;
	std::string mNoiseId;
public:
	Noise(bool del, std::string id, bool is_music);
	~Noise();
	void Update(Enemy& enemy, Uint32 deltaTicks);
};


#endif

