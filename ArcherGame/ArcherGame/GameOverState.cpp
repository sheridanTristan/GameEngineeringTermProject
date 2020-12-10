#include "GameOverState.h"
#include "MainMenuState.h"
#include "GameManager.h"
/*
 * Implementation of virtual methods in GameOverState.h
 * 
 */

void GameOverState::Enter()
{
	cout << "Entering GameOverState\n";
	GameEngine::Instance()->SetLeftMouse(false);

	bgSpriteTex = GameEngine::Instance()->LoadTexture("Img/GameOver.png");

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);

	m_pFont = TTF_OpenFont("Font/CONSOLAB.TTF", 36);

	menuButtons.push_back(new Button("Img/Retry.png", { 0,0,512,256 }, { 246,300,256,78 }));
	menuButtons.push_back(new Button("Img/Quit.png", { 0,0,512,256 }, { 522,300,256,78 }));
}

void GameOverState::Update()
{
	for (Button* button : menuButtons)
	{
		button->Update();
	}

	if (menuButtons[btn::retry]->Clicked())
	{
		// back to the first stage
	}

	if (menuButtons[btn::quit]->Clicked())
	{
		// store the score
		GameEngine::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}
}

void GameOverState::Render()
{
	SDL_RenderClear(GameEngine::Instance()->GetRenderer());

	bg->Render();

	for (Button* button : menuButtons)
	{
		button->Render();
	}
	string finalScore = "Final Score: 0"; // + to_string the score
	RenderFont(true, finalScore.c_str(), 330, 240);
	ScreenState::Render();
}

void GameOverState::Exit()
{
	cout << "Exiting GameOverState...\n";

	for (int i = 0; i < (int)menuButtons.size(); i++)
	{
		delete menuButtons[i];
		menuButtons[i] = nullptr;
	}
	menuButtons.clear();
	menuButtons.shrink_to_fit();
}