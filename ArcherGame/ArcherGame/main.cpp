#include <iostream>
#include "GameEngine.h"
#include "SDL.h"
#include "TestLevel.h"

int main(int argc, char* argv[]) {

	if (!GameEngine::Instance()->Init("ArcherGame", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1920, 1080, 0))
		return -1;

	GameEngine::Instance()->GetFSM()->ChangeState(new TestLevel());

	while (GameEngine::Instance()->IsRunning()) {
		GameEngine::Instance()->HandleEvents();
		GameEngine::Instance()->Update();
		GameEngine::Instance()->Render();
		SDL_Delay(10); //delay of 10 ms after every loop iteration

	}
	GameEngine::Instance()->Clean();
	return 0;
}