#include <iostream>
#include "GameEngine.h"
#include "SDL.h"
#include "TestLevel.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "VictoryState.h"
#include "GameManager.h"
int main(int argc, char* argv[]) {

	if (!GameEngine::Instance()->Init("ArcherGame", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1080, 720, 0))
		return -1;

	GameManager::Instance()->Initialze();
	
	GameEngine::Instance()->GetFSM()->ChangeState(new MainMenuState());
	
	

	while (GameEngine::Instance()->IsRunning()) {
		GameEngine::Instance()->HandleEvents();
		GameEngine::Instance()->Update();
		GameEngine::Instance()->Render();
		SDL_Delay(10); //delay of 10 ms after every loop iteration

	}
	GameEngine::Instance()->Clean();
	return 0;
}