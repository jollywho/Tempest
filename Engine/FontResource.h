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

class FontResource
{
public:
	static void AddFont(std::string id, std::string filename);
	static FontInfo& RequestFont(std::string id);
private:
	static std::map<std::string, FontInfo*> msFontResources;
};

#endif // FONTRESOURCE_H