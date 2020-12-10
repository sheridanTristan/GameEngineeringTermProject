#pragma once
#include "SpriteEx.h"

using namespace std;

class Bird : public SpriteExAnimated
{
private:
	void UpdateBird();
public:


	//float position = 0;

	double x = 0;
	double y =0;

	unsigned int startTime;



	Bird(SDL_Texture* tex, double x, double y);
	~Bird();

	virtual void Render();
	virtual void Update();
	void MoveBirdLeft();
	

};