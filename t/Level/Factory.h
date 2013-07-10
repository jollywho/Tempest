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

struct ActionData { bool del; int loops; };
struct AttackData { bool del; std::string bulletId; int speed; int rot; int interval; };
struct MoveData { bool del; int move_type; int speed; int dest_x; int dest_y; int dir_type; };
struct NoiseData { bool del; std::string id; bool is_music; };

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

