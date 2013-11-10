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
#include "ResourceLoader.h"
#include "SpriteResource.h"
#include "FontResource.h"
#include "SFX.h"
#include "Pattern/Explosion.h"

std::string ResourceLoader::msDir;

std::istream& operator >> (std::istream& is, Resource::Texture& data)
{	is >> data.id >> data.filename >> data.width >> data.height; return is;}

std::istream& operator >> (std::istream& is, Resource::Sprite& data)
{
	is >> data.id >> data.filename >> data.width >> data.height >> data.inteval
		>> data.maxClips >> data.vert; return is;
}

std::istream& operator >> (std::istream& is, Resource::RotSprite& data)
{
	is >> data.id >> data.filename >> data.width >> data.height
		>> data.interval >> data.maxClips >> data.start >> data.end
		>> data.destWidth >> data.destHeight >> data.pivotX
		>> data.pivotY >> data.rotInterval; return is;
}

std::istream& operator >> (std::istream& is, Resource::Sound& data)
{ is >> data.id >> data.filename; return is;}

std::istream& operator >> (std::istream& is, Resource::Font& data)
{ is >> data.id >> data.filename; return is;}

std::istream& operator >> (std::istream& is, Resource::Music& data)
{ is >> data.id >> data.filename; return is;}

std::istream& operator >> (std::istream& is, Resource::Explosion& data)
{	is >> data.id >> data.spriteId >> data.magnitude >> data.delay >> data.offsetX
		 >> data.offsetY >> data.residue; return is;}

void ResourceLoader::ReadFile(std::string dir, std::string file_name)
{
    std::ifstream file;
	std::string meta;
    std::string filename = file_name;
	filename.insert(0, "Script/");
	msDir = dir;
    file.open(filename.c_str(), std::ios_base::in);

    if (!file.is_open()) {
        printf("***Error: opening file: %s ***\n", file_name);
        return;}

    while (!file.eof())
    {
        file >> meta;
		if (meta == ":" + msDir + ":")
		{
			while (meta != "--")
			{
				file >> meta;
				if (meta == "Texture")
				{
					Resource::Texture tx;
					file >> tx;
					SpriteResource::AddTexture(msDir, tx.id, tx.filename, tx.width, tx.height);
				}
				if (meta == "Sprite")
				{
					Resource::Sprite sp;
					file >> sp;
					SpriteResource::AddResource(msDir, sp.id, sp.filename, sp.width, sp.height, sp.inteval, sp.maxClips, sp.vert);
				}
				if (meta == "RotSprite")
				{
					Resource::RotSprite rs;
					file >> rs;
					SpriteResource::AddRotationResource(msDir, rs.id, rs.filename, rs.width, rs.height, rs.interval, rs.maxClips, rs.start,
						rs.end, rs.destWidth, rs.destHeight, rs.pivotX, rs.pivotY, rs.rotInterval);
				}
				if (meta == "Sound")
				{
					Resource::Sound sd;
					file >> sd;
					SFX::AddSoundResource(sd.id, sd.filename);
				}
				if (meta == "Font")
				{
					Resource::Font ft;
					file >> ft;
					FontResource::AddFont(ft.id, ft.filename);
				}
				//music
				if (meta == "Explosion")
				{
					Resource::Explosion ex;
					file >> ex;
					Explosion::AddExplosionInfo(ex.id, ex.spriteId, ex.magnitude, ex.delay, ex.offsetX, ex.offsetY, ex.residue);
				}
			}
		}
    }
    file.close();
}