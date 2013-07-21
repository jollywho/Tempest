#pragma once
#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace Resource
{
	struct Texture
	{
		std::string id;
		std::string filename;
		int width;
		int height;
	};
	struct Sprite
	{
		std::string id;
		std::string filename;
		int width;
		int height;
		int inteval;
		int maxClips;
		bool vert;
	};
	struct RotSprite
	{
		std::string id;
		std::string filename;
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
	struct Sound{std::string id; std::string filename;};
	struct Music{std::string id; std::string filename;};

	struct Explosion
	{
		std::string id;
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
	static void ReadFile(std::string dir, std::string file_name="resx.dat");
	static std::string msDir;
};
enum Resx
{
	Texture = 1,
	Sprite = 2,
	RotSprite = 3,
	Font = 4,
	Sound = 5,
	Music = 6,
	Explosion = 7,
};
std::istream& operator >> (std::istream& is, Resource::Texture& data);
std::istream& operator >> (std::istream& is, Resource::Sprite& data);
std::istream& operator >> (std::istream& is, Resource::RotSprite& data);
std::istream& operator >> (std::istream& is, Resource::Sound& data);
std::istream& operator >> (std::istream& is, Resource::Music& data);
std::istream& operator >> (std::istream& is, Resource::Explosion& data);


#endif