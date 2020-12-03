#include "GameManager.h"

GameManager* GameManager::Instance()
{
    static GameManager* gm = new GameManager();
    return gm;

}

void GameManager::Initialze()
{
    GameEngine::Instance()->GetAudioManager()->LoadSound("Audio/drawbow.wav", AudioScope::GLOBAL, "Draw bow");
    GameEngine::Instance()->GetAudioManager()->LoadSound("Audio/bowrelease.wav", AudioScope::GLOBAL, "Bow release");
}
