#pragma once
#include "SpriteEx.h"
#include <math.h>

class Arrow :public SpriteExAnimated
{
public:
	float g = 5.0f;
	double x = 0;
	double y = 0;
	float launchVelocity = 0;
	

	unsigned int startTime;

	float dx=0.0;
	float dy=0.0;

	Arrow(SDL_Texture* tex, double x, double y, double a,float velocity) :SpriteExAnimated(tex, x, y, a)
	{
		m_DX = x;
		m_DY =y;
		this->x = x;
		this->y = y;
		spriteSrcRect = {80,1246,194,82};
		spriteDestRect = {(int)x,(int)y,30,15};
		m_dRadius = 5;
		launchVelocity = velocity;
		startTime = SDL_GetTicks();
		angle = a;
		dx = (float)cos((angle) * M_PI / 180);
		dy = (float)sin((angle) * M_PI / 180);
	}
	void Update() {
		float newX = (launchVelocity * (SDL_GetTicks() - startTime)/1000.0);
		angle=(float)(atan2(m_Y-y,m_X-x))*180/M_PI;
		//std::cout << newX<<std::endl;
		//std::cout << angle;
		
		m_X += (dx * (launchVelocity/50));
		m_Y += (dy * (launchVelocity /50)) - (-g * (float)pow((SDL_GetTicks() - startTime) / 1000.0, 2) / 2);
		this->UpdateDestRect();
	}
};
