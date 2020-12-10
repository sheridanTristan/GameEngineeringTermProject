#include "GameLevel2.h"
#include "GameEngine.h"

void GameLevel2::Enter()
{
    bgSpriteTex = GameEngine::Instance()->LoadTexture("Img/Stages/Stage2.png");

    GameState::Enter();


}