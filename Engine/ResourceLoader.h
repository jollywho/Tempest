#pragma once
#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

	struct Sound
	{
		std::string id;
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


	//Static image interface class for storing and using images as sprites.
	class ResourceLoader
	{
	public:
		static void ReadFile(std::string dir);

	};
std::istream& operator >> (std::istream& is, Sound& data);
std::istream& operator >> (std::istream& is, Sprite& data);

#endif