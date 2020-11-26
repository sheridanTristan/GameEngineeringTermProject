#include "TestLevel.h"
#include "GameEngine.h"

TestLevel::TestLevel() {

}
void TestLevel::Enter() {
	bgSpriteTex = GameEngine::Instance()->LoadTexture("Img/Grid.jpg");
	GameEngine::Instance()->GetAudioManager()->LoadSound("Audio/drawbow.wav",AudioScope::GLOBAL,"Draw bow");
	

	GameState::Enter();
}