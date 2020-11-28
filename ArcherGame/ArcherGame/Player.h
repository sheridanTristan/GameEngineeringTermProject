#pragma once
#include "SpriteEx.h"
#include "Arrow.h"

using namespace std;

class Player :public SpriteExAnimated
{
private:
	void UpdatePlayer();
	bool m_bReleased = true;

	Arrow* playerArrow;
	
	enum state { MOUSE_UP, MOUSE_OVER, MOUSE_DOWN };
	int mx=0;
	int my=0;
	int pointX=0;
	int pointY=0;
public:
	Player(SDL_Texture* tex, double x, double y);
	~Player();
	void Update();
	void Render();
	void GetMouseInput();
	void ShootArrow(float velocity,float angle);
	void UpdateArrow();
};