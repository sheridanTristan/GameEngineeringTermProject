#pragma once
#include "GameEngine.h"
#include <vector>
#include <fstream>
#include "Player.h"
#include "Enemy.h"
class GameManager
{
private:
	std::vector<int> m_Scores;
	int m_currentScore;
	Enemy* enemy;
	Player* player;

public:
	static GameManager* Instance();
	void Initialze();
	void ReadScores(std::string textFile);
	std::vector<int> GetScores() { return m_Scores; }
	void StepTurn();
	void SetupLevel(Player* player, Enemy* enemy);
	bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2);
	void AddScore(int score);
	void WriteScores(std::string textFile);
};

