#include "GameLevel1.h"
#include "GameEngine.h"

void GameLevel1::Enter()
{
    bgSpriteTex = GameEngine::Instance()->LoadTexture("Img/Stages/Stage1.png");

    GameState::Enter();


}