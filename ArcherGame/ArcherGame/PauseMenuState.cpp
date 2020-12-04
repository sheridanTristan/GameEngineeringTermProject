#include "PauseMenuState.h"
#include "MainMenuState.h"

/*
 * Implementation of virtual methods in PauseMenuState.h 
 *
 */

void PauseMenuState::Enter()
{
	cout << "Entering PauseMenuState\n";

	cout << "StateMachine vector:\n";
	vector<ScreenState*> currentVector = GameEngine::Instance()->GetFSM()->GetStates();
	cout << "Current vector size: " << currentVector.size();
	GameEngine::Instance()->SetLeftMouse(false);

	m_pFont = TTF_OpenFont("Font/CONSOLAB.TTF", 36);

	menuButtons.push_back(new Button("Img/Resume.png", { 0,0,512,256 }, { 384,280,256,78 }));
	menuButtons.push_back(new Button("Img/Quit.png", { 0,0,512,256 }, { 384,400,256,78 }));
}

void PauseMenuState::Update()
{
	for (Button* button : menuButtons)
	{
		button->Update();
	}

	if (menuButtons[btn::resume]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->PopState();
	}

	else if (menuButtons[btn::exit]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}
}

void PauseMenuState::Render()
{
	SDL_SetRenderDrawBlendMode(GameEngine::Instance()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 0, 153, 204, 10);
	SDL_Rect rect = { 357, 224, 324, 324 };
	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &rect);
	for (Button* button : menuButtons)
	{
		button->Render();
	}
	string paused = "Paused";
	RenderFont(true, paused.c_str(), 470, 240);
	ScreenState::Render();
}

void PauseMenuState::Exit()
{
	cout << "Exiting PauseMenu...\n";

	for (int i = 0; i < (int)menuButtons.size(); i++)
	{
		delete menuButtons[i];
		menuButtons[i] = nullptr;
	}
	menuButtons.clear();
	menuButtons.shrink_to_fit();
}