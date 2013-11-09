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