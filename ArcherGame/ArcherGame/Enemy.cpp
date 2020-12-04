#include "Enemy.h"
#include "GameEngine.h"

Enemy::Enemy(SDL_Texture* tex, double x, double y) : Player(tex, x, y)

{
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
	if (turn) {
		GameEngine::Instance()->GetAudioManager()->PlaySound("Draw bow");

		this->ShootArrow();

		GameEngine::Instance()->GetAudioManager()->PlaySound("Bow release");

		this->SetTurn(false);
	}
	this->UpdateArrow();
}

void Enemy::ShootArrow()
{
	//determine random angle and velocity
	float angle = 180.0f;
	float velocity = 1000.0f;

	enemyArrow = new Arrow(texture, m_X, m_Y, angle, velocity);
}

void Enemy::UpdateArrow() {
	if (enemyArrow)
	{
		enemyArrow->Update();
	}
}