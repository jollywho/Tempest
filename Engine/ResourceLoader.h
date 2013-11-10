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
	struct Font{std::string id; std::string filename;};
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

class ResourceLoader
{
public:
	static void ReadFile(std::string dir, std::string file_name="resx.dat");
	static std::string msDir;
};

std::istream& operator >> (std::istream& is, Resource::Texture& data);
std::istream& operator >> (std::istream& is, Resource::Sprite& data);
std::istream& operator >> (std::istream& is, Resource::RotSprite& data);
std::istream& operator >> (std::istream& is, Resource::Sound& data);
std::istream& operator >> (std::istream& is, Resource::Font& data);
std::istream& operator >> (std::istream& is, Resource::Music& data);
std::istream& operator >> (std::istream& is, Resource::Explosion& data);


#endif