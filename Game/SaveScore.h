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
#pragma once
#ifndef SAVESCORE_H
#define SAVESCORE_H
#include <map>
#include <string>
#include <iostream>
#include <fstream>

namespace ScoreIO
{
	struct ScoreData
	{
		std::string mode;
		int rank;
		int stage;
		unsigned long long value;
		std::string name;
	};


	class SaveScore
	{
	private:
		//key: mode, rank
		static std::map<std::pair<std::string, int>, ScoreData> scores;
	public:
		static void LoadScores();
		static int SaveScores();
		static ScoreData GetScores(std::string mode, int rank);
		static void SetNewScore(std::string mode, int stage, unsigned long long value, std::string name);
		static void GenerateDefaults();
	};
} //namespace SCOREIO
std::ostream& operator << ( std::ostream& ins, const ScoreIO::ScoreData& data );
std::istream& operator >> (std::istream& is, ScoreIO::ScoreData& data);

#endif