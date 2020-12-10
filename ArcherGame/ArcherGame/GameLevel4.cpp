#include "GameLevel4.h"
#include "GameEngine.h"

void GameLevel4::Enter()
{
    bgSpriteTex = GameEngine::Instance()->LoadTexture("Img/Stages/Stage2.png");

    GameState::Enter();


}