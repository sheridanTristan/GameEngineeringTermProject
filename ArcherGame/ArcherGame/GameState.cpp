#include "GameState.h"
#include "GameEngine.h"

void GameState::Enter()
{
	//	bgSpriteTex = Game::Instance()->LoadTexture("background.png");
	archerSpriteTex = GameEngine::Instance()->LoadTexture("Img/Archer.png");

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);

	player = new Player(archerSpriteTex, bgDestRect.w * 0.10, bgDestRect.h - 100);
	enemy = new Enemy(archerSpriteTex, bgDestRect.w * 0.90, bgDestRect.h - 100);

	GameEngine::Instance()->GetAudioManager()->LoadSound("Audio/drawbow.wav", AudioScope::GLOBAL, "Draw bow");
	GameEngine::Instance()->GetAudioManager()->LoadSound("Audio/bowrelease.wav", AudioScope::GLOBAL, "Bow release");
}


void GameState::Update()
{
	if (player) player->Update();
}


void GameState::Render()
{
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 0, 0, 0, 255); //set background window color
	SDL_RenderClear(GameEngine::Instance()->GetRenderer()); //clear the screen

	bg->Render();

	if (player) {
		player->Render(); 
	}

	if (enemy) {
		enemy->Render();
	}

	ScreenState::Render();


}


void GameState::Exit()
{


}


