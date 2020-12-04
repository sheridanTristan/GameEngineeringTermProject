#include "Player.h"

#include "GameEngine.h"
#include <math.h>
#include "GameManager.h"
Player::Player(SDL_Texture* tex, double x, double y) :
	SpriteExAnimated(tex, x - 50, y - 50, 0)
{
	SDL_Texture* appleTexture = GameEngine::Instance()->LoadTexture("Img/Apple.png");
	turn = true;
	spriteSrcRect = { 0,0,330,450 };
	spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50)  ,70,80 };
	apple = new Apple(appleTexture, m_X-20, m_Y-60);

}

Player::~Player() {

}

void Player::Render() {
	this->SpriteExAnimated::Render();
	if (playerArrow) {
		playerArrow->Render();
	}
	SDL_RenderDrawRect(GameEngine::Instance()->GetRenderer(), &powerBarBorder);
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 255, 0, 0, 255);//making the power meter red


	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &powerBarFill);//making the power meter red



	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &powerBarFill);//making the power meter red
}

void Player::Update() {
	this->UpdatePlayer();
}

void Player::UpdatePlayer() {
	if (turn) {
		GetMouseInput();

	}
	this->UpdateArrow();

	//GetMouseInput();
}

void Player::GetMouseInput() {
	float launchVelocity;


	if (GameEngine::Instance()->GetLeftMouse() && m_bReleased) {
		m_iFrame = MOUSE_DOWN;
		m_bReleased = false;
		pointX = GameEngine::Instance()->GetMouseX();
		pointY = GameEngine::Instance()->GetMouseY();
		GameEngine::Instance()->GetAudioManager()->PlaySound("Draw bow");
	}
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




		//SDL_Log("Mouse Button 1 (left) is pressed.");


		this->ShootArrow(launchVelocity, -(atan2(my - pointY, pointX - mx)) * 180 / M_PI);
		m_iFrame = MOUSE_OVER;
	//	SDL_Log("Mouse Button 1 (left) is released.");
		GameEngine::Instance()->GetAudioManager()->PlaySound("Bow release");
		GameManager::Instance()->StepTurn();

	}
	else
		//SDL_Log("Mouse UP");

	if (m_bReleased == false)
	{
		mx = GameEngine::Instance()->GetMouseX();
		my = GameEngine::Instance()->GetMouseY();

		if (pointX - mx > my - pointY) {
			launchVelocity = pointX - mx;
		}
		else
			launchVelocity = my - pointY;
		power = launchVelocity / 10;
		powerBarFill = { 70,610,power,10 };
	}

}


void PlayerTurn() {

}

void Player::ShootArrow(float velocity, float angle) {
	playerArrow = new Arrow(texture, m_X, m_Y, angle, velocity);
	cout << velocity << endl;
	cout << angle << endl;
	//cout << velocity << endl;
	//cout << angle << endl;
}

void Player::UpdateArrow() {
	if (playerArrow) {
		playerArrow->Update();
	}
}