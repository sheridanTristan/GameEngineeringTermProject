#include "Enemy.h"
#include "GameEngine.h"
#include "GameManager.h"
#include <stdlib.h> 

Enemy::Enemy(SDL_Texture* tex, double x, double y) : Player(tex, x, y)

{
	turn = false;
	m_turnTime = SDL_GetTicks();
	flippedDimensions = std::make_pair(true, false);
	spriteSrcRect = { 0,0,330,450 };
	spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50)  ,70,80 };
	m_turnTimeout = 1000;
	SDL_Texture* appleTexture = GameEngine::Instance()->LoadTexture("Img/Apple.png");
	turn = true;
	flippedDimensions = std::make_pair(true, false);
	spriteSrcRect = { 0,0,330,450 };
	spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50)  ,70,80 };
	apple = new Apple(appleTexture, m_X-35 , m_Y-60 );
}

Enemy::~Enemy()
{

}

void Enemy::Render()
{
	this->SpriteExAnimated::Render();
	if (enemyArrow) {
		enemyArrow->Render();
	}
}

void Enemy::Update()
{
	this->UpdateEnemy();

}

void Enemy::UpdateEnemy()
{
	if (turn ) {
		
		if (SDL_TICKS_PASSED(SDL_GetTicks(), m_turnTime + m_turnTimeout)) {
			GameEngine::Instance()->GetAudioManager()->PlaySound("Draw bow");

			this->ShootArrow();

			GameEngine::Instance()->GetAudioManager()->PlaySound("Bow release");

			GameManager::Instance()->StepTurn();
		}
		
	}
	this->UpdateArrow();
}

void Enemy::ShootArrow()
{
	float velocity = 0;
	//determine random angle and velocity
	
	//determine random angle and velocity
	float angle = rand() % (210 - 180 + 1) + 180;
	//cout << "angle is: " << angle<<endl;
	if (angle <= 210 && angle >= 205)
	{
		velocity = rand() % (350 - 300 + 1) + 300;
	}
	else if (angle <= 204 && angle >= 200)
	{
		velocity = rand() % (400 - 350 + 1) + 350;
	}
	else if (angle <= 199 && angle >= 195)
	{
		velocity = rand() % (460 - 400 + 1) + 400;
	}
	else if (angle <= 194 && angle >= 190)
	{
		velocity = rand() % (550 - 450 + 1) + 450;
	}
	else {
		velocity = rand() % (700 - 600 + 1) + 600;
	}
	//cout << "velocity is: " << velocity << endl;

	enemyArrow = new Arrow(texture, m_X, m_Y, angle, velocity);


}

void Enemy::UpdateArrow() {
	if (enemyArrow)
	{
		enemyArrow->Update();
	}
}