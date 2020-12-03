#include "PauseOptionMenuState.h"
#include <iostream>
#include "Game.h"
#include "MainMenuState.h"
#include "GameState.h"

using namespace std;


void LevelSelector::Enter()
{
	m_vButtons.push_back(new Button("Img/Stages/Stage1.png", { 1,1,401,81 }, { 412,200,200,80 }));
	m_vButtons.push_back(new Button("Img/Stages/Stage2.png", { 2,2,601,101 }, { 412,400,200,80 }));
	m_vButtons.push_back(new Button("Img/Stages/Stage3.png", { 3,3,801,121 }, { 412,200,200,80 }));
	m_vButtons.push_back(new Button("Img/Stages/Stage4.png", { 3,3,801,121 }, { 412,200,200,80 }));


}

void LevelSelector::Update()
{

	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	if (m_vButtons[btn::level1]->Clicked())
	{

		GameEngine::Instance()->GetFSM()->ChangeState(new GameState());
	}

	else if (m_vButtons[btn::level2]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->ChangeState(new GameState());

	}
	else if (m_vButtons[btn::level3]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->ChangeState(new GameState());

	}
	else
	{
		GameEngine::Instance()->GetFSM()->ChangeState(new GameState());
	}

}


void LevelSelector::Render()
{

	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 200, 264, 200, 200);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Game::Instance()->GetRenderer(), &rect);
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

