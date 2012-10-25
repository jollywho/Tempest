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
}
std::ostream& operator << ( std::ostream& ins, const ScoreIO::ScoreData& data );
std::istream& operator >> (std::istream& is, ScoreIO::ScoreData& data);

#endif