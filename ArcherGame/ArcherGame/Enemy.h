#pragma once
#include "Player.h"

class Enemy : public Player
{

private:
	bool turn;
	Uint32 m_turnTime;
	int m_turnTimeout;

public:
	Arrow* enemyArrow;
	Enemy(SDL_Texture* tex, double x, double y);
	~Enemy();
	void Update() override;

	void Render() override;

	void ShootArrow();
	void UpdateArrow();

	void UpdateEnemy();

	void SetTurn(bool t) { 
		if (t) {
			SetTurnTime(SDL_GetTicks());
		}
		
		turn = t; 
	
	}
	bool GetTurn() { return turn; }
	void SetTurnTime(Uint32 t) { m_turnTime = t; }
};