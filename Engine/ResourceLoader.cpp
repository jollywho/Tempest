#include "ResourceLoader.h"
#include "SpriteResource.h"
#include "SFX.h"
#include "Pattern/Explosion.h"

std::string ResourceLoader::msDir;

std::istream& operator >> (std::istream& is, Resource::Sprite& data)
{
	is >> data.id >> data.width >> data.height >> data.inteval >> data.maxClips
		>> data.vert; return is;
}

std::istream& operator >> (std::istream& is, Resource::Sound& data)
{ is >> data.id; return is;}

std::istream& operator >> (std::istream& is, Resource::Explosion& data)
{	is >> data.expId >> data.spriteId >> data.magnitude >> data.delay >> data.offsetX
		 >> data.offsetY >> data.residue; return is; }

void ResourceLoader::ReadFile(std::string dir)
{
    std::ifstream file;
	std::string meta;
    std::string filename = "resx.dat";
	msDir = dir;
    file.open(filename.c_str(), std::ios_base::in);

    if (!file.is_open()) {
        std::cout<<"Error: opening file 'resx.dat'."<<std::endl;
        return; }

    while (!file.eof())
    {
        file >> meta;
		if (meta == ":" + msDir + ":")
		{
			while (meta != "--")
			{
				file >> meta;
				if (meta == "Sound")
				{
					Resource::Sound sd;
					file >> sd;
					SFX::AddSoundResource(sd.id);
				}
				if (meta =="Sprite")
				{
					Resource::Sprite sp;
					file >> sp;
					SpriteResource::AddResource(msDir, sp.id, sp.width, sp.height, sp.inteval, sp.maxClips, sp.vert);
				}
				if (meta == "Explosion")
				{
					Resource::Explosion ex;
					file >> ex;
					Explosion::AddExplosionInfo(ex.expId, ex.spriteId, ex.magnitude, ex.delay, ex.offsetX, ex.offsetY, ex.residue);
				}
			}
		}
    }
    file.close();
}