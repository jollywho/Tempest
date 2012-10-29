#include "FontResource.h"

std::map<std::string, FontInfo*> FontResource::msFontResources;

void FontResource::AddFont(std::string filename)
{
	if (msFontResources.find(filename) == msFontResources.end())
	{
		FontInfo* temp_info = new FontInfo();
		temp_info->pSurface = Shared::LoadImage("Font/" + filename);
		temp_info->pFont = new NFont(SDL_GetVideoSurface(), temp_info->pSurface);
		printf("Added: Font/%s\n", filename.c_str());
		msFontResources.insert(std::make_pair(filename, temp_info));
	}
}

FontInfo& FontResource::RequestFont(std::string filename)
{
	auto temp = msFontResources.find(filename);
	if (temp->second == NULL)
		printf("***Error Opening: Font/%s***\n", filename.c_str());
	return *temp->second;
}