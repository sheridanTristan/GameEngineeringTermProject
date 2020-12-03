#include "MainMenuState.h"
#include "HighScoreState.h"
#include "GameManager.h"

/* 
 * Implementation of virtual methods in HighScoreState.h
 *
 */

void HighScoreState::Enter()
{
	cout << "Entering HighScoreState\n";
	GameEngine::Instance()->SetLeftMouse(false);

	m_pFont = TTF_OpenFont("Font/CONSOLAB.TTF", 36);

	menuButtons.push_back(new Button("Img/Back.png", { 0,0,512,256 }, { 400,620,256,78 }));

}

void HighScoreState::Update()
{
	for (Button* button : menuButtons)
	{
		button->Update();
	}

	if (menuButtons[btn::back]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->PopState();
	}

}

void HighScoreState::Render()
{
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 0, 153, 204, 255);
	SDL_Rect rect = { 64, 32, 896, 704 };
	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &rect);
	for (Button* button : menuButtons)
	{
		button->Render();
	}
	string paused = "High Scores";
	RenderFont(true, paused.c_str(), 420, 74);
	string scores;
	for (int i = 0; i < GameManager::Instance()->GetScores().size(); i++)
	{
		scores += GameManager::Instance()->GetScores()[i] +"\n";
	}
	RenderFont(true, scores.c_str(), 90, 110);

	ScreenState::Render();

}


void HighScoreState::Exit()
{
	cout << "Exiting HighScoreState...\n";

	for (int i = 0; i < (int)menuButtons.size(); i++)
	{
		delete menuButtons[i];
		menuButtons[i] = nullptr;
	}
	menuButtons.clear();
	menuButtons.shrink_to_fit();
	

}