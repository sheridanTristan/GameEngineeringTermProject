#include "Bird.h"
#include "GameEngine.h"
#include "GameManager.h"


Bird::Bird(SDL_Texture* tex, double x, double y) : SpriteExAnimated(tex, x + 100, y + 73 , 3)
{
	m_DX = 2.5;
	m_Y = 80;
	//m_DY = y;
	//this->x = x;
	//this->y = y;

	spriteSrcRect = { 0,0,100,73 };
	spriteDestRect = { (int)(m_X - 500),(int)(m_Y)  ,50,36 };

	m_dRadius = 5;

	AddAnimState("Bird", AnimStateDefinition(0, 3, 200,true,false));
	cout << "Bird Created\n";
}

Bird::~Bird() {

}

void Bird::Render() {

	this->SpriteExAnimated::Render();
	
	
}

void Bird::Update()
{
	this->UpdateBird();
	PlayState("Bird");
	this->UpdateDestRect();
}


void Bird::MoveBirdLeft()
{

	m_X -= m_DX;
	spriteSrcRect.x = spriteSrcRect.w * m_iFrame; //updates the animation
	if (m_X < 0)
	{
		m_X = 1300;
	}
	
	
	

}


void Bird::UpdateBird()
{

	
	MoveBirdLeft();

	
}


