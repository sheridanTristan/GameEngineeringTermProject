#include "GameManager.h"

GameManager* GameManager::Instance()
{
    static GameManager* gm = new GameManager();
    return gm;

}

void GameManager::Initialze()
{
    GameEngine::Instance()->GetAudioManager()->LoadSound("Audio/drawbow.wav", AudioScope::GLOBAL, "Draw bow");
    GameEngine::Instance()->GetAudioManager()->LoadSound("Audio/bowrelease.wav", AudioScope::GLOBAL, "Bow release");
    ReadScores("scores.txt");

    

}

void GameManager::StepTurn() {
    if (player->GetTurn()) {
        player->SetTurn(false);
        
        enemy->SetTurn(true);
    }
    else {
        enemy->SetTurn(false);
        
        player->SetTurn(true);
    }


}

void GameManager::SetupLevel(Player* player, Enemy* enemy) {
    this->player = player;
    this->enemy = enemy;
}


void GameManager::ReadScores(std::string textFile) {
    fstream file;
    file.open(textFile, ios::in);
    if (!file) {
        std::cout << "Could not open file " << textFile << "\n";
        return;
    }
    else {
        char ch;
        std::vector<int> scores;
        std::string score;
        while (!file.eof()) {
            file >> ch;
            if (ch != ';' && !file.eof()) {
                score.append(1, ch);
            }
            else {
                try {
                    int iScore = std::stoi(score);
                    scores.push_back(iScore);
                    std::cout << iScore << "\n";
                    score.clear();
                }
                catch (std::invalid_argument e) {
                    std::cout << "Invalid score\n";
                }
                
            }

        }
        file.close();
        m_Scores = scores;
        scores.clear();
    }
}

bool GameManager::CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2) {
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (r1 + r2));
}

void GameManager::AddScore(int score)
{
    m_Scores.push_back(score);
}

void GameManager::WriteScores(std::string textFile)
{
    fstream file;
    file.open(textFile, ios::out);
    if (file.is_open()) 
    {
        for (int i = 0; i < m_Scores.size();i++) 
        {
            int score = m_Scores[i];
            file << score;
            if (i < m_Scores.size() - 1) {
                file << ";";
            }
        }
        file.close();
    }


}
