#include "GameLevel3.h"
#include "GameEngine.h"

void GameLevel3::Enter()
{
    bgSpriteTex = GameEngine::Instance()->LoadTexture("Img/Stages/Stage3.png");

    GameState::Enter();


}