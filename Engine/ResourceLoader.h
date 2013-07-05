#pragma once
#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace Resource
{
	struct Sound{std::string id;};
	struct Font {std::string id;};
	struct RotSprite
	{
		std::string id;
		int width;
		int height;
		int interval;
		int maxClips;
		int start;
		int end;
		int destWidth;
		int destHeight;
		int pivotX;
		int pivotY;
		int rotInterval;
	};
	struct Sprite
	{
		std::string id;
		int width;
		int height;
		int inteval;
		int maxClips;
		bool vert;
	};
	struct Explosion
	{
		std::string expId;
		std::string spriteId;
		int magnitude;
		int delay;
		int offsetX;
		int offsetY;
		bool residue;
	};
}

//Static image interface class for storing and using images as sprites.
class ResourceLoader
{
public:
	static void ReadFile(std::string dir);
	static std::string msDir;
};
enum Resx
{
	Sound = 1,
	Sprite = 2,
	RotSprite = 3,
	Font = 4,
	Music = 5,
	Explosion = 6,
};
std::istream& operator >> (std::istream& is, Resource::Sound& data);
std::istream& operator >> (std::istream& is, Resource::Sprite& data);
std::istream& operator >> (std::istream& is, Resource::Explosion& data);

#endif