#pragma once
#include <vector>
#include <iostream>

#include "Button.h"
#include "ScreenState.h"
#include "GameEngine.h"
#include "SpriteEx.h"

using namespace std;

class PauseMenuState : public ScreenState
{

protected:
	SDL_Texture* bgSpriteTex;
	SpriteEx* bg;

	vector<Button*> menuButtons;
	enum btn { resume, exit };

public:
	PauseMenuState() {}
	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() {}
};