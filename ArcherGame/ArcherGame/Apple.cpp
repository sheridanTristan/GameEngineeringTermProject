#include "Apple.h"

Apple::Apple(SDL_Texture* tex, double x, double y) :
	SpriteExAnimated(tex, x, y,0) {
	
	m_DX = x;
	m_DY = y;
	spriteSrcRect={0,0,512,512};
	spriteDestRect = {(int)x,(int)y,25,25};
	m_dRadius = 6;
}

Apple:: ~Apple() {
	SDL_DestroyTexture(texture);
}