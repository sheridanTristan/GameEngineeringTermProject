#include <stdio.h>
#include "GameEngine.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "VictoryState.h"

int main(int argc, char** argv) {
	if (!GameEngine::Instance()->Init("Archery Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0)) {
		
		return -1;
	}
	else {

		GameEngine::Instance()->GetFSM()->ChangeState(new MainMenuState());
		// GameEngine::Instance()->GetFSM()->ChangeState(new GameOverState());
		// GameEngine::Instance()->GetFSM()->ChangeState(new VictoryState());
		
	}
	while (GameEngine::Instance()->IsRunning()) {

		GameEngine::Instance()->HandleEvents();
		GameEngine::Instance()->Update();
		GameEngine::Instance()->Render();
		SDL_Delay(10);
	}

	GameEngine::Instance()->Clean();
	return 0;
}