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

	vector<Button*> menuButtons;
	enum btn { back };
	int m_ScoreSeperation;

public:
	HighScoreState() {}
	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() {}
};