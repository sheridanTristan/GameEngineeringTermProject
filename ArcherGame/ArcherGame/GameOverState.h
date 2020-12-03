#pragma once
#include <vector>
#include <iostream>

#include "Button.h"
#include "ScreenState.h"
#include "GameEngine.h"
#include "SpriteEx.h"

using namespace std;

class GameOverState : public ScreenState
{

protected: 
	SDL_Texture* bgSpriteTex;
	SpriteEx* bg;

	vector<Button*> menuButtons;
	enum btn {retry, quit};

public: 
	GameOverState() {}
	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() {}
};