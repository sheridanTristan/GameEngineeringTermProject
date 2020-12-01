#pragma once
#include "Player.h"

class Enemy : public Player
{

private:
	Arrow* enemyArrow;
	bool turn;

public:
	Enemy(SDL_Texture* tex, double x, double y);
	~Enemy();
	void Update() override;

	void Render() override;

	void ShootArrow();
	void UpdateArrow();

	void UpdateEnemy();

	void SetTurn(bool t) { turn = t; }
	bool GetTurn() { return turn; }
};