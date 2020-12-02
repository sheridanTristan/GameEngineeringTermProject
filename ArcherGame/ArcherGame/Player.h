#pragma once
#include "SpriteEx.h"
#include "Arrow.h"

using namespace std;

class Player :public SpriteExAnimated
{
private:
	void UpdatePlayer();
	bool m_bReleased = true;
	int power;
	SDL_Rect powerBarBorder = { 70,610,100,10 };
	SDL_Rect powerBarFill = { 70,610,0,10 };
	

	Arrow* playerArrow;

	bool turn;
	
	enum state { MOUSE_UP, MOUSE_OVER, MOUSE_DOWN };
	int mx=0;
	int my=0;
	int pointX=0;
	int pointY=0;
public:
	Player(SDL_Texture* tex, double x, double y);
	~Player();
	virtual void Update();
	virtual void Render();
	void GetMouseInput();
	void ShootArrow(float velocity,float angle);
	void UpdateArrow();

	void SetTurn(bool t){ turn = t; }
	bool GetTurn() { return turn; }
};