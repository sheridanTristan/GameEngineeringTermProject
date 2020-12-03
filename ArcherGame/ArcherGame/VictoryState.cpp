#include "VictoryState.h"
#include "MainMenuState.h"

/*
 * Implementation of virtual methods in VictoryState.h
 *
 */

void VictoryState::Enter()
{
	cout << "Entering VictoryState\n";
	GameEngine::Instance()->SetLeftMouse(false);

	bgSpriteTex = GameEngine::Instance()->LoadTexture("Img/Victory.png");

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);

	m_pFont = TTF_OpenFont("Font/CONSOLAB.TTF", 36);

	menuButtons.push_back(new Button("Img/Resume.png", { 0,0,512,256 }, { 388,280,256,78 }));
}

void VictoryState::Update()
{
	for (Button* button : menuButtons)
	{
		button->Update();
	}

	if (menuButtons[btn::cont]->Clicked())
	{
		// move to the next stage
	}
}

void VictoryState::Render()
{
	SDL_RenderClear(GameEngine::Instance()->GetRenderer());

	bg->Render();

	for (Button* button : menuButtons)
	{
		button->Render();
	}

	string currentScore = "Current Score: "; // + to_string the score
	RenderFont(true, currentScore.c_str(), 330, 240);

	ScreenState::Render();
}

void VictoryState::Exit()
{
	cout << "Exiting VictoryState...\n";

	for (int i = 0; i < (int)menuButtons.size(); i++)
	{
		delete menuButtons[i];
		menuButtons[i] = nullptr;
	}
	menuButtons.clear();
	menuButtons.shrink_to_fit();
}