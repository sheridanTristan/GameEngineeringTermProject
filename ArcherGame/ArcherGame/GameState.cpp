#include "GameState.h"
#include "GameEngine.h"
#include "PauseMenuState.h"
#include "GameManager.h"
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

	player = new Player(archerSpriteTex, bgDestRect.w * 0.15, bgDestRect.h - 100);
	enemy = new Enemy(archerSpriteTex, bgDestRect.w * 0.95, bgDestRect.h - 100);
	GameManager::Instance()->SetupLevel(player, enemy);
	
}


void GameState::Update()
{
	if (player) {
		player->Update(); 
	}

	if (enemy) {
		enemy->Update(); 
	}
	
	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_ESCAPE) == 1)
	{
		GameEngine::Instance()->GetFSM()->PushState(new PauseMenuState());
		return;
	}
	if (player->apple && enemy->apple&&(enemy->playerArrow||player->playerArrow)) {
		CheckCollision();
	}


}
void GameState::CheckCollision() 
{
	//cout << "checkCollision called";
	player->SetTurn(true);//remove this when needed used for testing if I dont remove this I am a scrub from Kamil Kania 
	if (player->GetTurn()) {
		//cout << player->playerArrow->GetX()<<endl;
		//cout << enemy->apple->GetX() << endl;
		if (CircleCollisionTest(player->playerArrow->GetX(), player->playerArrow->GetY(),
			enemy->apple->GetX(), enemy->apple->GetY()+10,
			player->playerArrow->GetRadius(), enemy->apple->GetRadius())) 
		{
			cout << "Player has hit the enemies apple!!\n";
		}
	}
	else if (enemy->GetTurn()) {
		if (CircleCollisionTest(enemy->playerArrow->GetX(), enemy->playerArrow->GetY(),
			player->apple->GetX(), player->apple->GetY(),
			enemy->playerArrow->GetRadius(), player->apple->GetRadius()))
		{
			cout << "Enemy has hit the players apple!! Enemy Wins!\n";
		}
	}

	
}


void GameState::Render()
{
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 0, 0, 0, 255); //set background window color
	SDL_RenderClear(GameEngine::Instance()->GetRenderer()); //clear the screen

	bg->Render();

	if (player) {
		player->Render();
		player->apple->Render();
	}

	if (enemy) {
		enemy->Render();
		enemy->apple->Render();
	}

	ScreenState::Render();
}


void GameState::Exit()
{
	SDL_DestroyTexture(bgSpriteTex);
	SDL_DestroyTexture(archerSpriteTex);
	delete bg;
	delete player;
	delete enemy;
	GameEngine::Instance()->GetAudioManager()->UnloadSound(AudioScope::SESSION);
	GameEngine::Instance()->GetAudioManager()->UnloadMusic(AudioScope::SESSION);
	

}


