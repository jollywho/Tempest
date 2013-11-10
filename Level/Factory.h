/* Tempest - C++ Danmakufu Game for SDL
*
*  Copyright (C) 2013 Kevin Vollmer.
*  
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*  
ÅÅ*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <map>

#include "CreatorImpl.h"

class Enemy;
class Creator;
class Action;

struct ActionData { bool del; int loops;};
struct AttackData { bool del; std::string bulletId; int speed; int rot; int interval;};
struct MoveData { bool del; int move_type; int speed; int dest_x; int dest_y; int dir_type;};
struct NoiseData { bool del; std::string id; bool is_music;};

struct EnData
{
	std::string id;
	int originX;
	int originY;
	int size;
	std::list<Action*> actions;
};

class Factory
{
public:
	static Enemy* create(const std::string& classname, int x, int y, std::list<Action*>& actions);
	static void registerit(const std::string& classname, Creator* creator);
	static void Factory::ReadFile(std::string dir, std::list<Enemy*>& cache);
private:
	static std::map<std::string, Creator*>& get_table();
};

std::istream& operator >> (std::istream& is, EnData& data);
std::istream& operator >> (std::istream& is, ActionData& data);
std::istream& operator >> (std::istream& is, AttackData& data);
std::istream& operator >> (std::istream& is, MoveData& data);
std::istream& operator >> (std::istream& is, NoiseData& data);

#define REGISTER(classname) \
	private: \
	static const CreatorImpl<classname> creator;

#define REGISTERIMPL(classname) \
	const CreatorImpl<classname> classname::creator(#classname);

#endif //_FACTORY_H_

