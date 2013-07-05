#include "ResourceLoader.h"
#include "SpriteResource.h"
#include "SFX.h"

std::istream& operator >> (std::istream& is, Resource::Sprite& data)
{
	is >> data.id;
	is >> data.width;
	is >> data.height;
	is >> data.inteval;
	is >> data.maxClips;
	is >> data.vert;
	return is;
}

std::istream& operator >> (std::istream& is, Resource::Sound& data)
{
	is >> data.id;
	return is;
}

void ResourceLoader::ReadFile(std::string dir)
{
	std::ifstream file;
	std::string meta;
	Resource::Sound data;
	Resource::Sprite info;
	std::string filename = "resx.dat";
	file.open(filename.c_str(), std::ios_base::in);

	if (!file.is_open())
	{
		std::cout<<"Error: opening file 'resx.dat'."<<std::endl;
		file.open(filename.c_str(), std::ios_base::in);
	}
	else
	{
		while (!file.eof())
		{
			file >> meta;
			if (meta == ":" + dir + ":")
			{
				while (meta != "--")
				{
					file >> meta;
					if (file.fail()) std::cin.clear();
					if (meta == "Sound") 
					{
						file >> data;
						SFX::AddSoundResource(data.id);
					}
					if (meta == "Sprite") 
					{
						file >> info;
						SpriteResource::AddResource(dir, info.id, info.width, info.height, info.inteval, info.maxClips, info.vert);
					}
				}
			}
		}
	}
	file.close();
}