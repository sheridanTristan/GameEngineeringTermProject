#include <stdlib.h>
#include <time.h>

#include "MainMenuState.h"
#include "PauseMenuState.h"
#include "HighScoreState.h"
#include "TestLevel.h"
#include "GameLevel1.h"
/*	
 *	Implementation of virtual methods in ScreenState.h
 *	
 */

// Create buttons when you reach the main menu
void MainMenuState::Enter()
{
	cout << "Entering Main Menu State\n";
	GameEngine::Instance()->SetLeftMouse(false);
	
	srand(time(NULL));
	int img = rand() % 4 + 1;
	string filePath = "Img/Stages/Stage" + to_string(img) + ".png";
	const char* file = filePath.c_str();
	bgSpriteTex = GameEngine::Instance()->LoadTexture(file);

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);

	menuButtons.push_back(new Button("Img/Play.png", { 0,0,512,256 }, { 400,200,256,128 }));
	menuButtons.push_back(new Button("Img/HiScore.png", { 0,0,512,256 }, { 400,335,256,128 }));
	menuButtons.push_back(new Button("Img/Quit.png", { 0,0,512,256 }, { 400,470,256,128 }));
	GameEngine::Instance()->GetAudioManager()->LoadMusic("audio/mainmenu.mp3",AudioScope::SESSION,"menumusic");
	GameEngine::Instance()->GetAudioManager()->PlayMusic("menumusic");
}

// Update buttons located on the menu
void MainMenuState::Update()
{

	for (Button* button : menuButtons)
	{
		button->Update();
	}

	// if play is clicked, prompt the user to enter name
	if (menuButtons[btn::play]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->ChangeState(new GameLevel1);
		return;
	}
	// if exit is clicked, game closes
	else if (menuButtons[btn::exit]->Clicked())
	{
		SDL_Delay(500);
		GameEngine::Instance()->QuitGame();
	}

	// View all the high scores
	else if (menuButtons[btn::highscore]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->PushState(new HighScoreState());
		return;
	}
}

void MainMenuState::Render()
{
	SDL_RenderClear(GameEngine::Instance()->GetRenderer());

	bg->Render();

	for (Button* button : menuButtons)
	{
		button->Render();
	}

	ScreenState::Render();
}

void MainMenuState::Exit()
{
	cout << "Exiting MainMenu...\n";
	
	for (int i = 0; i < (int)menuButtons.size(); i++)
	{
		delete menuButtons[i];
		menuButtons[i] = nullptr;
	}

	menuButtons.clear();
	menuButtons.shrink_to_fit();
	GameEngine::Instance()->GetAudioManager()->ToggleMusic();
	GameEngine::Instance()->GetAudioManager()->UnloadMusic(AudioScope::SESSION);
	
	SDL_DestroyTexture(bgSpriteTex);
	delete bg;
	
}