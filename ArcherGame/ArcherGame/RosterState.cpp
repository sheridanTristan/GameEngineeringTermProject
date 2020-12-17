#include "RosterState.h"
#include <iostream>
#include "GameEngine.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "LevelSelector.h"

using namespace std;

void RosterState::Enter()
{
	m_vButtons.push_back(new Button("Img/Resume.png", { 0,0,512,256 }, { 500,500,100,64 }));
	archerSpriteTex = GameEngine::Instance()->LoadTexture("Img/Archer.png");
	sprite1SrcRect = { 0,0,330,450 };
	sprite1DestRect = { 400 , 200 , 70 , 80 };
	enemySpriteTex = GameEngine::Instance()->LoadTexture("Img/Archer_1.png");
	sprite2SrcRect = {0,0,330,450};
	sprite2DestRect = { 400, 300, 70, 80 };
	birdSpriteTex = GameEngine::Instance()->LoadTexture("Img/Bird.png");
	sprite3SrcRect = { 0, 0, 100, 73};
	sprite3DestRect = { 400 , 400 , 50 , 36 };
	m_pFont = TTF_OpenFont("Font/CONSOLAB.TTF", 36);
}

void RosterState::Update()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();
	if (m_vButtons[btn::level1]->Clicked())
	{
		GameEngine::Instance()->GetFSM()->ChangeState(new LevelSelector());
	}
}

void RosterState::Render()
{
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 300, 500, 200, 200);
	SDL_Rect rect = { 300, 150, 456, 456 };
	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &rect);

	string player = "Player";
	RenderFont(true, player.c_str(), 490, 200);
	string enemy = "Enemy";
	RenderFont(true, enemy.c_str(), 490, 300);
	string bird = "Bird";
	RenderFont(true, bird.c_str(), 490, 400);


	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();

	if (SDL_RenderCopyEx(GameEngine::Instance()->GetRenderer(), archerSpriteTex, &sprite1SrcRect, &sprite1DestRect, 0, nullptr, SDL_FLIP_NONE)) {
	}
	if (SDL_RenderCopyEx(GameEngine::Instance()->GetRenderer(), enemySpriteTex, &sprite2SrcRect, &sprite2DestRect, 0, nullptr, SDL_FLIP_NONE)) {
	}
	if (SDL_RenderCopyEx(GameEngine::Instance()->GetRenderer(), birdSpriteTex, &sprite3SrcRect, &sprite3DestRect, 0, nullptr, SDL_FLIP_NONE)) {
	}
	
	ScreenState::Render();
}

void RosterState::Exit()
{
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}
