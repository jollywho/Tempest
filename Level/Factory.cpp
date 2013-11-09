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
#include "Factory.h"
#include "Action/Action.h"
#include "Action/Attack.h"
#include "Action/Move.h"
#include "Action/Noise.h"

std::istream& operator >> (std::istream& is, ActionData& data)
{
	is >> data.del >> data.loops; return is;
}

std::istream& operator >> (std::istream& is, AttackData& data)
{
	is >> data.del >> data.bulletId >> data.speed >> data.rot >> data.interval; return is;}

std::istream& operator >> (std::istream& is, MoveData& data)
{
	is >> data.del >> data.move_type >> data.speed >> data.dest_x 
		>> data.dest_y >> data.dir_type; 
	return is;
}

std::istream& operator >> (std::istream& is, NoiseData& data)
{
	is >> data.del >> data.id >> data.is_music;
	return is;
}

std::istream& operator >> (std::istream& is, EnData& data)
{
    size_t size;
    std::string meta;

    is >> data.id >> data.originX >> data.originY >> size;
    for (size_t i=0; i<size; i++)
    {
        is >> meta;
		if (meta == "Action") 	{ ActionData act;	is >> act;	data.actions.push_back(new Action(act.del, act.loops));	}
		if (meta == "Attack") 	{ AttackData atk;	is >> atk;	data.actions.push_back(new Attack(atk.del, atk.bulletId, atk.speed, atk.rot, atk.interval));	}
		if (meta == "Move")		{ MoveData mv;	is >> mv;		data.actions.push_back(new Move(mv.del, mv.move_type, mv.speed, mv.dest_x, mv.dest_y, mv.dir_type));	}
		if (meta == "Noise")	{ NoiseData ns;	is >> ns;		data.actions.push_back(new Noise(ns.del, ns.id, ns.is_music));	}	
    }
    return is;
}

void Factory::registerit(const std::string& classname, Creator* creator)
{
	get_table()[classname] = creator;
}

Enemy* Factory::create(const std::string& classname, int x, int y, std::list<Action*>& actions)
{
	std::map<std::string, Creator*>::iterator i;
	i = get_table().find(classname);

	if(i != get_table().end())
		return i->second->create(x, y, actions);
	else
		return (Enemy*)NULL;
}

std::map<std::string, Creator*>& Factory::get_table()
{
	static std::map<std::string, Creator*> table;
	return table;
}

void Factory::ReadFile(std::string filename, std::list<Enemy*>& cache)
{
    std::ifstream file;
	std::string meta;
    file.open(filename.c_str(), std::ios_base::in);

    if (!file.is_open()) {
        std::cout<<"**Error: opening file: " + filename << " ***" << std::endl;
        return; }

    while (!file.eof())
    {
		EnData en;
        file >> en;
		cache.push_back(Factory::create(en.id, en.originX, en.originY, en.actions));
    }
    file.close();
}