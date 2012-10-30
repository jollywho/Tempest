#include "SpriteResource.h"

std::map<std::pair<std::string, std::string>, SpriteInfo*> SpriteResource::mResources;
std::map<std::pair<std::string, std::string>, RotationInfo*> SpriteResource::mRotResources;

void SpriteResource::AddResource(std::string dirname, std::string filename,
	int width, int height, int interval, int maxClips, bool vert)
{
	if (mResources.find(std::make_pair(dirname, filename)) == mResources.end())
	{
		SpriteInfo* temp = new SpriteInfo();
		temp->pSurface = Shared::LoadImage("Image/" + dirname + "/" + filename);
		temp->width = width;
		temp->height = height;
		temp->interval = interval;
		temp->maxClips = maxClips;
		temp->pClips = new SDL_Rect[maxClips];
		if (!vert)Shared::SetFrames(temp->pClips, maxClips, width, height, 0);
		else Shared::SetVertFrames(temp->pClips, maxClips, width, height);
		mResources.insert(std::make_pair(std::make_pair(dirname, filename), temp));
	}
}

SpriteInfo& SpriteResource::RequestResource(std::string dirname, std::string filename)
{
	auto temp = mResources.find(std::make_pair(dirname, filename));
	if (temp->second == NULL)
		printf("***Error Opening: %s***\n", filename.c_str());
	return *temp->second;
}
RotationInfo& SpriteResource::RequestRotationResource(std::string dirname, std::string filename)
{
	auto temp = mRotResources.find(std::make_pair(dirname, filename));
	if (temp->second == NULL)
		printf("***Error Opening: %s***\n", filename.c_str());
	return *temp->second;
}

void SpriteResource::ClearResourceDir(std::string dirname)
{
	for (auto it = mResources.begin(); it != mResources.end();) 
	{
		if ((it)->first.first == dirname)
		{
			delete (*it).second;
			it = mResources.erase(it);
		}
		else
			it++;
	}
	for (auto it = mRotResources.begin(); it != mRotResources.end();) 
	{
		if ((it)->first.first == dirname)
		{
			delete (*it).second;
			it = mRotResources.erase(it);
		}
		else
			it++;
	}
}

void SpriteResource::ClearAllResources()
{
	for (auto it = mResources.begin(); it != mResources.end();) 
	{
        delete (*it).second;
		it = mResources.erase(it);
	}
	for (auto it = mRotResources.begin(); it != mRotResources.end();) 
	{
        delete (*it).second;
		it = mRotResources.erase(it);
	}
}

void SpriteResource::AddRotationResource(std::string dirname, std::string filename, 
	int width, int height, int interval, int maxClips, 
	int start, int end, int destWidth, int destHeight, 
	int pivotX, int pivotY, int rotInterval)
{
	if (mRotResources.find(std::make_pair(dirname, filename)) == mRotResources.end())
	{
		RotationInfo* temp = new RotationInfo();
		temp->width = width;
		temp->height = height;
		temp->interval = interval;
		temp->maxClips = maxClips;
		temp->pClips = new SDL_Rect[maxClips];
		temp->start = start;
		temp->end = end;
		temp->rotInterval = rotInterval;
		Shared::SetFrames(temp->pClips, maxClips, width, height, 0);
		temp->pSurface = new SDL_Surface**[temp->maxClips];
		Shared::SetRotationFrames(temp->pClips,
			Shared::LoadImage("Image/" + dirname + "/" + filename),
			temp->maxClips,temp->width,temp->height,
			temp->pSurface,start, end, destWidth, destHeight, pivotX, pivotY, rotInterval);
		mRotResources.insert(std::make_pair(std::make_pair(dirname, filename), temp));
	}
}