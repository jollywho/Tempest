#include "SpriteResource.h"

std::map<std::pair<std::string, std::string>, SpriteInfo*> SpriteResource::resources;
std::map<std::pair<std::string, std::string>, RotationInfo*> SpriteResource::rot_resources;

void SpriteResource::AddResource(std::string dirname, std::string filename,
	int width, int height, int interval, int clip_count, bool vert)
{
	if (resources.find(std::make_pair(dirname, filename)) == resources.end())
	{
		SpriteInfo* temp = new SpriteInfo();
		temp->surface = Shared::load_image("Image/" + dirname + "/" + filename);
		temp->width = width;
		temp->height = height;
		temp->interval = interval;
		temp->clip_count = clip_count;
		temp->clips = new SDL_Rect[clip_count];
		if (!vert)Shared::setFrames(temp->clips, clip_count, width, height, 0);
		else Shared::setVertFrames(temp->clips, clip_count, width, height);
		resources.insert(std::make_pair(std::make_pair(dirname, filename), temp));
	}
}

SpriteInfo& SpriteResource::RequestResource(std::string dirname, std::string filename)
{
	auto temp = resources.find(std::make_pair(dirname, filename));
	return *temp->second;
}
RotationInfo& SpriteResource::RequestRotationResource(std::string dirname, std::string filename)
{
	auto temp = rot_resources.find(std::make_pair(dirname, filename));
	return *temp->second;
}

void SpriteResource::ClearResourceDir(std::string dirname)
{
	for (auto it = resources.begin(); it != resources.end();) 
	{
		if ((it)->first.first == dirname)
		{
			delete (*it).second;
			it = resources.erase(it);
		}
		else
			it++;
	}
	for (auto it = rot_resources.begin(); it != rot_resources.end();) 
	{
		if ((it)->first.first == dirname)
		{
			delete (*it).second;
			it = rot_resources.erase(it);
		}
		else
			it++;
	}
}

void SpriteResource::ClearAllResources()
{
	for (auto it = resources.begin(); it != resources.end();) 
	{
        delete (*it).second;
		it = resources.erase(it);
	}
	for (auto it = rot_resources.begin(); it != rot_resources.end();) 
	{
        delete (*it).second;
		it = rot_resources.erase(it);
	}
}

void SpriteResource::AddRotationResource(std::string dirname, std::string filename, 
	int width, int height, int interval, int clip_count, 
	int start, int end, int destWidth, int destHeight, 
	int pivotX, int pivotY, int rotInterval)
{
	if (rot_resources.find(std::make_pair(dirname, filename)) == rot_resources.end())
	{
		RotationInfo* temp = new RotationInfo();
		temp->width = width;
		temp->height = height;
		temp->interval = interval;
		temp->clip_count = clip_count;
		temp->clips = new SDL_Rect[clip_count];
		temp->start = start;
		temp->end = end;
		temp->rotInterval = rotInterval;
		Shared::setFrames(temp->clips, clip_count, width, height, 0);
		temp->rot_surface = new SDL_Surface**[temp->clip_count];
		Shared::setRotationFrames(temp->clips,
			Shared::load_image("Image/" + dirname + "/" + filename),
			temp->clip_count,temp->width,temp->height,
			temp->rot_surface,start, end, destWidth, destHeight, pivotX, pivotY, rotInterval);
		rot_resources.insert(std::make_pair(std::make_pair(dirname, filename), temp));
	}
}