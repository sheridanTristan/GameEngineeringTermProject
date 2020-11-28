#pragma once
#include "Player.h"

class Enemy : public Player
{
public:
	Enemy(SDL_Texture* tex, double x, double y);
	~Enemy();
	void Update() override;
};