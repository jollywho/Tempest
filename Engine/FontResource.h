#ifndef FONTRESOURCE_H
#define FONTRESOURCE_H

#include "Shared.h"
#include "NFont.h"
#include <map>

struct FontInfo
{
	SDL_Surface* pSurface;
	NFont* pFont;

	~FontInfo()
	{
		SDL_FreeSurface(pSurface);
		delete pFont;
	}
};

/*
Static font class for storing and using fonts
*/
class FontResource
{
public:
	static void AddFont(std::string filename);
	static FontInfo& RequestFont(std::string filename);
private:
	static std::map<std::string, FontInfo*> msFontResources;


};

#endif 