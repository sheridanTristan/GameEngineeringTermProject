#include "Player.h"
#include "GameEngine.h"

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

}

void Player::Update() {

	this->UpdatePlayer();
}

void Player::UpdatePlayer(){

	GetMouseInput();

}

void Player::GetMouseInput() {
	if (GameEngine::Instance()->GetLeftMouse() && m_bReleased) {
		m_iFrame = MOUSE_DOWN;
		m_bReleased = false;
		pointX = GameEngine::Instance()->GetMouseX();
		pointY = GameEngine::Instance()->GetMouseY();
		SDL_Log("Mouse Button 1 (left) is pressed.");
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
		m_iFrame = MOUSE_UP;
		
		//check to see which is the greater distince to use as power/launchVelocity
		if (pointX - mx > my - pointY) {
			launchVelocity = pointX - mx;
		}
		else
			launchVelocity = my - pointY;

	ShootArrow(launchVelocity,-(atan2(my-pointY,pointX-mx))*180/M_PI);
		m_iFrame = MOUSE_OVER;
		SDL_Log("Mouse Button 1 (left) is released.");
		GameEngine::Instance()->GetAudioManager()->PlaySound("Bow release");
		
>>>>>>> parent of 7dd23a6... Revert "Pull from master"
	}
	else
		m_iFrame = MOUSE_UP;

	if (m_bReleased == false)
	{

		mx = GameEngine::Instance()->GetMouseX();
		my = GameEngine::Instance()->GetMouseY();
		cout << pointX << endl;
		cout << pointY << endl;
		cout << mx << endl;
		cout << my << endl;
	}
}