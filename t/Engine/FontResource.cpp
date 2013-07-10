#include "FontResource.h"

std::map<std::string, FontInfo*> FontResource::msFontResources;

void FontResource::AddFont(std::string id, std::string filename)
{
	if (msFontResources.find(id) == msFontResources.end())
	{
		FontInfo* temp_info = new FontInfo();
		temp_info->pSurface = Shared::LoadImage("Font/" + filename);
		temp_info->pFont = new NFont(SDL_GetVideoSurface(), temp_info->pSurface);
		printf("Added: Font/%s\n", filename.c_str());
		msFontResources.insert(std::make_pair(id, temp_info));
	}
}

FontInfo& FontResource::RequestFont(std::string id)
{
	auto temp = msFontResources.find(id);
	if (temp->second == NULL)
		printf("***Error Opening: Font/%s***\n", id.c_str());
	return *temp->second;
}