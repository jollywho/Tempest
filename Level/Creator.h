#ifndef _CREATOR_H_
#define _CREATOR_H_

#include <string>
#include <list>
#include "Action/Action.h"

class Creator
{
public:
	Creator(const std::string& classname);
	virtual ~Creator() {};

	virtual Enemy* create(int x, int y, std::list<Action*>& actions) = 0;
};

#endif //_CREATOR_H_

