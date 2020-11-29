#include "Player.h"
#include "GameEngine.h"
#include <math.h>

Player::Player(SDL_Texture* tex, double x, double y) :
	SpriteExAnimated(tex, x - 50, y - 50, 0)
{
	spriteSrcRect = { 0,0,330,450 };
	spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50)  ,70,80 };

}

Player::~Player() {

}

void Player::Render() {
	this->SpriteExAnimated::Render();
	if (playerArrow) {
		playerArrow->Render();
	}
}

void Player::Update() {
	this->UpdatePlayer();
}

void Player::UpdatePlayer(){
	GetMouseInput();
}

void Player::GetMouseInput() {
	float launchVelocity;

	if (GameEngine::Instance()->GetLeftMouse() && m_bReleased) {
		m_iFrame = MOUSE_DOWN;
		m_bReleased = false;
		pointX = GameEngine::Instance()->GetMouseX();
		pointY = GameEngine::Instance()->GetMouseY();
	}
<<<<<<< HEAD
	else if (!GameEngine::Instance()->GetLeftMouse())
=======
	else if (!GameEngine::Instance()->GetLeftMouse()&& !m_bReleased)
		SDL_Log("Mouse Button 1 (left) is pressed.");
		GameEngine::Instance()->GetAudioManager()->PlaySound("Draw bow");
		
	}
	else if (!GameEngine::Instance()->GetLeftMouse() && !m_bReleased)
>>>>>>> parent of 7dd23a6... Revert "Pull from master"
	{
		
		m_bReleased = true;
<<<<<<< HEAD
		m_iFrame = MOUSE_OVER;
		SDL_Log("Mouse Button 1 (left) is released.");
=======
	else if (!GameEngine::Instance()->GetLeftMouse() && !m_bReleased)
	{
		
		m_bReleased = true;
		m_iFrame = MOUSE_UP;
		
		//check to see which is the greater distince to use as power/launchVelocity
		if (pointX - mx > my - pointY) {
			launchVelocity = pointX - mx;
		}
		else
			launchVelocity = my - pointY;
		SDL_Log("Mouse Button 1 (left) is pressed.");
		GameEngine::Instance()->GetAudioManager()->PlaySound("Draw bow");

	ShootArrow(launchVelocity,-(atan2(my-pointY,pointX-mx))*180/M_PI);
		m_iFrame = MOUSE_OVER;
		SDL_Log("Mouse Button 1 (left) is released.");
		GameEngine::Instance()->GetAudioManager()->PlaySound("Bow release");
		
>>>>>>> parent of 7dd23a6... Revert "Pull from master"
	}
	else
		SDL_Log("Mouse UP");

	if (m_bReleased == false)
	{
		mx = GameEngine::Instance()->GetMouseX();
		my = GameEngine::Instance()->GetMouseY();
	}
	UpdateArrow();
}

void Player::ShootArrow(float velocity,float angle) {
	playerArrow = new Arrow(texture, m_X, m_Y, angle,velocity);
}

void Player::UpdateArrow() {
	if (playerArrow) {
		playerArrow->Update();
	}
}