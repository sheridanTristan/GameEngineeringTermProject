#pragma once
#include "Player.h"
#include "SDL_mixer.h"
#include "ScreenState.h"
#include "SpriteEx.h"
#include <iostream>
#include "Enemy.h"
using namespace std;

class GameState : public ScreenState
{
protected:
	SDL_Texture* bgSpriteTex; //load and store background sprite tex
	SDL_Texture* archerSpriteTex;
	SDL_Texture* enemySpriteTex;

	SpriteEx* bg;

	Player* player;
	Enemy* enemy;

public:
	GameState() {}
	virtual void Update();
	virtual void Render();
	virtual void Enter();
	void Exit();
	void Resume() { cout << "Resuming Game..." << endl; }
	bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2)
	{
		return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (r1 + r2));

	}

	void CheckCollision();
};