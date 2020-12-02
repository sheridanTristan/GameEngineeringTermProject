#include "Score.h"

Score::Score()
{
	score = 0.0f;
}

void Score::modScore(float no)
{
	score += no;
}

float Score::getScore()
{
	return score;
}