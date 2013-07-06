/*
 * CreatorImpl.h
 * 
 *  Created on: April 14, 2013
 *      Author: David J. Rager
 *       Email: djrager@fourthwoods.com
 *
 * This code is hereby released into the public domain per the Creative Commons
 * Public Domain dedication.
 *
 * http://http://creativecommons.org/publicdomain/zero/1.0/
 */
#ifndef _CREATORIMPL_H_
#define _CREATORIMPL_H_

#include <string>

#include "Creator.h"

template <class T>
class CreatorImpl : public Creator
{
public:
	CreatorImpl<T>(const std::string& classname) : Creator(classname) {}
	virtual ~CreatorImpl<T>() {}

	virtual Enemy* create() { return new T; }
	//virtual Enemy* create() { return new T(x,y,id,list<action>& actions); } ???
};

#endif //_CREATORIMPL_H_

