#ifndef _CREATOR_H_
#define _CREATOR_H_

#include <string>

class Enemy;

class Creator
{
public:
	Creator(const std::string& classname);
	virtual ~Creator() {};

	virtual Enemy* create() = 0;
};

#endif //_CREATOR_H_

