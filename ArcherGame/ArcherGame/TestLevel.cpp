#include "TestLevel.h"
#include "GameEngine.h"

TestLevel::TestLevel() {

}
void TestLevel::Enter() {
	bgSpriteTex = GameEngine::Instance()->LoadTexture("Img/Grid.jpg");
	
	

	GameState::Enter();
}
