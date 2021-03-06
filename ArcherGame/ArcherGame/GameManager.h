#pragma once
#include "GameEngine.h"
#include <vector>
#include <fstream>
#include "Player.h"
#include "Enemy.h"
#include <algorithm>

#define NUM_SCORES 10

#include "Bird.h"
#define FLAPPING_CHANNEL 4

class GameManager
{
private:
	std::vector<int> m_Scores;
	int m_currentScore;
	Enemy* enemy;
	Player* player;
	Bird* bird;


public:
	bool gameOver = false;
	bool win = false;
	static GameManager* Instance();
	void Initialze();
	void ReadScores(std::string textFile);
	std::vector<int> GetScores() { return m_Scores; }
	void StepTurn();
	void SetupLevel(Player* player, Enemy* enemy, Bird* bird);
	bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2);
	int GetLastScore();
	void AddScore(int score);
	void WriteScores(std::string textFile);
	int GetCurrentScore() { return m_currentScore; }
	void BirdKill();
	void SetCurrentScore(int score) { m_currentScore = score; }
	void EndGame(bool playerWin);
	void UpdateScores();
};

