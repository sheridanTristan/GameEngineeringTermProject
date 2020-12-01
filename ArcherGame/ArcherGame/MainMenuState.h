#pragma once
#include <vector>
#include <iostream>

#include "Button.h"
#include "ScreenState.h"
#include "GameEngine.h"
#include "SpriteEx.h"

using namespace std;

class MainMenuState : public ScreenState
{

protected:
	SDL_Texture* bgSpriteTex;
	SpriteEx* bg;

	vector<Button*> menuButtons;
	enum btn {play, highscore, exit};

public: 
	MainMenuState() {}
	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() {}
};