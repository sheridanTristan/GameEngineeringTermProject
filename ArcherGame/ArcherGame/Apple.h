#pragma once

#include "SpriteEx.h"
using namespace std;

class Apple : public SpriteExAnimated {

private:

public :
	Apple(SDL_Texture* tex, double x, double y);
	~Apple();
};