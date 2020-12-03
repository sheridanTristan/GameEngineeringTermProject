#include "Score.h"

Score::Score()
{
	score = 0.0f;
}

Score::Score(float no)
{
	score = no;
}

void Score::modScore(float no)
{
	score += no;
}

float Score::getScore()
{
	return score;
}