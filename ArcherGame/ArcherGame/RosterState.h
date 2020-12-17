#include "ScreenState.h"
#include <vector>
#include "Button.h"
using namespace std;

class RosterState : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	enum btn { level1, level2, level3, level4 };
	SDL_Texture* archerSpriteTex;
	SDL_Texture* enemySpriteTex;
	SDL_Texture* birdSpriteTex;
	SDL_Rect sprite1DestRect;
	SDL_Rect sprite1SrcRect;
	SDL_Rect sprite2DestRect;
	SDL_Rect sprite2SrcRect;
	SDL_Rect sprite3DestRect;
	SDL_Rect sprite3SrcRect;

public:
	RosterState() {}
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume() {}
};

