#pragma once

#include "ScreenState.h"
#include <vector>
#include "Button.h"
using namespace std;

class LevelSelector : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	enum btn { level1, level2, level3 };

public:
	LevelSelector() {}
	void Update(); // Method prototype.
	void Render();
	void Enter();
	void Exit();
	void Resume() {}

};