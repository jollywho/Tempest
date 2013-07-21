#include "ResourceLoader.h"
#include "SpriteResource.h"
#include "SFX.h"
#include "Pattern/Explosion.h"

std::string ResourceLoader::msDir;

std::istream& operator >> (std::istream& is, Resource::Texture& data)
{	is >> data.id >> data.filename >> data.width >> data.height; return is; }

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

std::istream& operator >> (std::istream& is, Resource::Music& data)
{ is >> data.id >> data.filename; return is;}

std::istream& operator >> (std::istream& is, Resource::Explosion& data)
{	is >> data.id >> data.spriteId >> data.magnitude >> data.delay >> data.offsetX
		 >> data.offsetY >> data.residue; return is; }

void ResourceLoader::ReadFile(std::string dir, std::string file_name)
{
    std::ifstream file;
	std::string meta;
    std::string filename = file_name;
	filename.insert(0, "Script/");
	msDir = dir;
    file.open(filename.c_str(), std::ios_base::in);

    if (!file.is_open()) {
        std::cout<<"***Error: opening file: " << file_name << "***\n"<<std::endl;
        return; }

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
				if (meta =="Sprite")
				{
					Resource::Sprite sp;
					file >> sp;
					SpriteResource::AddResource(msDir, sp.id, sp.filename, sp.width, sp.height, sp.inteval, sp.maxClips, sp.vert);
				}
				if (meta =="RotSprite")
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