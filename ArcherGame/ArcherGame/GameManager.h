#pragma once
#include "GameEngine.h"
class GameManager
{
public:
	static GameManager* Instance();
	void Initialze();
	bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2);

};

