#include "Enemy.h"

Enemy::Enemy(SDL_Texture* tex, double x, double y) : Player(tex, x, y)
{
	spriteSrcRect = { 0,0,330,450 };
	spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50)  ,70,80 };
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{

}