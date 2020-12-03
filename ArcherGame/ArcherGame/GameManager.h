#pragma once
#include "GameEngine.h"
#include <vector>
#include <fstream>
class GameManager
{
private:
	std::vector<int> m_Scores;
public:
	static GameManager* Instance();
	void Initialze();
	void ReadScores(std::string textFile);
	std::vector<int> GetScores() { return m_Scores; }
};

