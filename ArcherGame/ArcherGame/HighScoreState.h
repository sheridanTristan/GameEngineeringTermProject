#pragma once
#include <vector>
#include <iostream>

#include "Button.h"
#include "ScreenState.h"
#include "GameEngine.h"
#include "SpriteEx.h"

using namespace std;

class HighScoreState : public ScreenState
{

protected:
	SDL_Texture* bgSpriteTex;
	SpriteEx* bg;

	vector<Button*> menuButtons;
	enum btn { back };

public:
	HighScoreState() {}
	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() {}
};