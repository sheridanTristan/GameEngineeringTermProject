#include "LevelSelector.h"
#include <iostream>
#include "GameEngine.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "GameLevel1.h"
#include "GameLevel2.h"
#include "GameLevel3.h"
#include "GameLevel4.h"

using namespace std;

void LevelSelector::Enter()
{
	m_vButtons.push_back(new Button("Img/Level1.png", { 0,0,512,256 }, { 420,300,100,64}));
	m_vButtons.push_back(new Button("Img/Level2.png", { 0,0,512,256 }, { 540,300,100,64}));
	m_vButtons.push_back(new Button("Img/Level3.png", { 0,0,512,256 }, { 420,380,100,64}));
	m_vButtons.push_back(new Button("Img/Level4.png", { 0,0,512,256 }, { 540,380,100,64}));
}

void LevelSelector::Update()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();
	if (m_vButtons[btn::level1]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->ChangeState(new GameLevel1());
	}
	else if (m_vButtons[btn::level2]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->ChangeState(new GameLevel2());
	}
	else if (m_vButtons[btn::level3]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->ChangeState(new GameLevel3());
	}
	else if (m_vButtons[btn::level4]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->ChangeState(new GameLevel4());
	}
}

void LevelSelector::Render()
{
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 200, 264, 200, 200);
	SDL_Rect rect = { 400, 250, 256, 256 };
	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &rect);
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	ScreenState::Render();
}

void LevelSelector::Exit()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}
