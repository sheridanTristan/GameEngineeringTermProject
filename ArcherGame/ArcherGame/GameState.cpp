#include "GameState.h"
#include "GameEngine.h"
#include "PauseMenuState.h"
#include "GameManager.h"
#include "VictoryState.h"
#include "GameOverState.h"
void GameState::Enter()
{
	m_pFont = TTF_OpenFont("Font/CONSOLAB.TTF", 36);
	gameOverTimeout = 2000;
	gameOverStart = SDL_GetTicks();
	GameManager::Instance()->win = false;
	GameManager::Instance()->gameOver = false;
	//	bgSpriteTex = Game::Instance()->LoadTexture("background.png");
	archerSpriteTex = GameEngine::Instance()->LoadTexture("Img/Archer.png");
	enemySpriteTex = GameEngine::Instance()->LoadTexture("Img/Archer_1.png");
	birdSpriteTex = GameEngine::Instance()->LoadTexture("Img/Bird.png");

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);

	player = new Player(archerSpriteTex, bgDestRect.w * 0.15, bgDestRect.h - 100);
	enemy = new Enemy(enemySpriteTex, bgDestRect.w * 0.95, bgDestRect.h - 100);

	bird = new Bird(birdSpriteTex, bgDestRect.w * 0.95, bgDestRect.h - 1000);
	GameManager::Instance()->SetupLevel(player, enemy, bird);

	
}


void GameState::Update()
{
	if (player) {
		player->Update(); 
	}

	if (enemy) {
		enemy->Update(); 
	}
	if (bird) {
		bird->Update();
	}
	
	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_ESCAPE) == 1)
	{
		GameEngine::Instance()->GetFSM()->PushState(new PauseMenuState());
		return;
	}
	if ((player->apple && enemy->apple) && !GameManager::Instance()->gameOver) {
		
			CheckCollision();
	}
	if (GameManager::Instance()->gameOver && SDL_TICKS_PASSED(SDL_GetTicks(),gameOverStart + gameOverTimeout)) {
		if (GameManager::Instance()->gameOver && GameManager::Instance()->win)
		{
			GameEngine::Instance()->GetFSM()->ChangeState(new VictoryState);
		}
		else if (GameManager::Instance()->gameOver && !GameManager::Instance()->win)
		{
			GameEngine::Instance()->GetFSM()->ChangeState(new GameOverState);
		}
	}
	



}
void GameState::CheckCollision() 
{
	//cout<<enemy->GetTurn();
	//cout << "checkCollision called";
	//player->SetTurn(true);//remove this when needed used for testing if I dont remove this I am a scrub from Kamil Kania 
	if (player->playerArrow != nullptr) {
		//cout << player->playerArrow->GetX()<<endl;
		//cout << enemy->apple->GetX() << endl;
		if (CircleCollisionTest(player->playerArrow->GetX(), player->playerArrow->GetY(),
			enemy->apple->GetX(), enemy->apple->GetY()+10,
			player->playerArrow->GetRadius(), enemy->apple->GetRadius())) 
		{
			cout << "Player has hit the enemies apple!!\n";
			GameManager::Instance()->EndGame(true,200);
			gameOverStart = SDL_GetTicks();

		}
	}
	if ( enemy->enemyArrow) {
		if (CircleCollisionTest(enemy->enemyArrow->GetX(), enemy->enemyArrow->GetY(),
			player->apple->GetX(), player->apple->GetY()+10,
			enemy->enemyArrow->GetRadius(), player->apple->GetRadius()))
		{
			cout << "Enemy has hit the players apple!! Enemy Wins!\n";
			
			GameManager::Instance()->EndGame(false);
			gameOverStart = SDL_GetTicks();
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

	if (GameManager::Instance()->gameOver) {
		char gameWinner[32];
		std::string gameOverText = "Game Over!";
		if (GameManager::Instance()->win) {
			sprintf_s(gameWinner, 32, "Player wins!");
		}
		else {
			sprintf_s(gameWinner, 32, "You lose!");
		}
		const SDL_Surface surface = *SDL_GetWindowSurface(GameEngine::Instance()->GetWindow());

		RenderFont(true, gameOverText.c_str(), (surface.w / 2) -  50, 200);
		RenderFont(true, gameWinner, (surface.w / 2) - 50, 240);


	}

	if (bird) {
		bird->Render();
	}

	ScreenState::Render();
}


void GameState::Exit()
{
	SDL_DestroyTexture(bgSpriteTex);
	SDL_DestroyTexture(archerSpriteTex);
	SDL_DestroyTexture(enemySpriteTex);
	SDL_DestroyTexture(birdSpriteTex);
	delete bg;
	delete player;
	delete enemy;
	delete bird;
	GameEngine::Instance()->GetAudioManager()->UnloadSound(AudioScope::SESSION);
	GameEngine::Instance()->GetAudioManager()->UnloadMusic(AudioScope::SESSION);
	

}


