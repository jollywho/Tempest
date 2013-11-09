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
#include "SaveScore.h"

std::ostream& operator << ( std::ostream& ins, const ScoreIO::ScoreData& data )
{
	ins << data.mode << std::endl;
	ins << data.rank << std::endl;
	ins << data.stage << std::endl;
	ins << data.value << std::endl;
	ins << data.name << std::endl;
	return ins;
}

std::istream& operator >> (std::istream& is, ScoreIO::ScoreData& data)
{
	is >> data.mode;
	is >> data.rank;
	is >> data.stage;
	is >> data.value;
	is >> data.name;
	return is;
}

namespace ScoreIO
{
	std::map<std::pair<std::string, int>, ScoreData> SaveScore::scores;

	void SaveScore::LoadScores()
	{
		std::ifstream file;
		ScoreData data;
		std::string filename = "Scores.dat";
		file.open(filename.c_str(), std::ios_base::in);

		if (!file.is_open())
		{
			std::cout<<"Error: opening file 'Scores.dat'."<<std::endl;
			std::cout<<"Created: new 'Scores.dat'."<<std::endl;
			file.open(filename.c_str(), std::ios_base::in | std::ios_base::trunc);
			GenerateDefaults();
			SaveScores();
		}
		else
		{
			while ( file >> data )
				scores.insert(std::make_pair(std::make_pair(data.mode, data.rank), data));
		}
		file.close();
	}

	int SaveScore::SaveScores()
	{
		std::ofstream file;
		file.open("Scores.dat", std::ofstream::out);
		if (!file.is_open())
		{
			std::cout<<"Error: opening file 'Scores.dat'."<<std::endl;
			return 1;
		}

		for (auto it = scores.begin(); it != scores.end(); it++)
		{
			file << it->second;
		}
		file.close();
		return 0;
	}

	ScoreData SaveScore::GetScores(std::string mode, int rank)
	{
		std::map<std::pair<std::string, int>, ScoreData>::iterator it = scores.find(std::make_pair(mode, rank));
		ScoreData temp;
		if (it != scores.end())
			temp = it->second;
		else
			std::cout<<"Error retrieving score data: "<< mode << " " << rank << std::endl;
		return temp;
	}

	void SaveScore::SetNewScore(std::string mode, int stage, unsigned long long value, std::string name)
	{
		std::map<std::pair<std::string, int>, ScoreData> newscores;
		ScoreData newscore;
		newscore.mode = mode; newscore.name = name; newscore.rank = 100; newscore.stage = stage; newscore.value = value;
		for (auto it = scores.begin(); it != scores.end(); it++)
		{
			if (it->second.mode == mode)
			{
				if (it->second.value < value)
				{
					if (it->second.rank < newscore.rank) 
						newscore.rank = it->second.rank;
					it->second.rank++;
					if (it->second.rank <= 5)
						newscores.insert(std::make_pair(std::make_pair(it->second.mode, it->second.rank), it->second));
				}
				else
					newscores.insert(std::make_pair(it->first, it->second));
			}
			else
				newscores.insert(std::make_pair(it->first, it->second));
		}
		newscores.insert(std::make_pair(std::make_pair(newscore.mode, newscore.rank), newscore));
		scores.clear();
		scores = newscores;
		SaveScores();
	}

	void SaveScore::GenerateDefaults()
	{
		ScoreData normal_default =	{"Normal", 1, 6, 300000, "AAAAAAAA"};
		ScoreData ultra_default =	{"Ultra", 1, 5, 500000, "BBBBBBBB"};
		ScoreData insane_default =	{"Insane", 1, 4, 900000, "CCCCCCCC"};

		for (int i=0; i < 5; i++)
		{
			scores.insert(std::make_pair(std::make_pair(normal_default.mode, normal_default.rank), normal_default));
			scores.insert(std::make_pair(std::make_pair(ultra_default.mode, ultra_default.rank), ultra_default));
			scores.insert(std::make_pair(std::make_pair(insane_default.mode, insane_default.rank), insane_default));
			normal_default.rank++; normal_default.value -= 1999;
			ultra_default.rank++; ultra_default.value -= 2999;
			insane_default.rank++; insane_default.value -= 4999;
		}
	}
}