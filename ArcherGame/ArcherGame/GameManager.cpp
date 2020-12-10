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
    GameEngine::Instance()->GetAudioManager()->LoadSound("Audio/applehit.wav",AudioScope::GLOBAL,"Apple hit");
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

int GameManager::GetLastScore()
{
    return m_Scores[m_Scores.size()-1];
}

void GameManager::AddScore(int score)
{
    m_Scores.push_back(score);
    
    
}

void GameManager::WriteScores(std::string textFile)
{
    sort(m_Scores.begin(), m_Scores.end(), greater<int>());
    fstream file;
    file.open(textFile, ios::out);
    if (file.is_open()) 
    {
        int scoresToPrint = (m_Scores.size() < NUM_SCORES) ? m_Scores.size() : NUM_SCORES;
        for (int i = 0; i < scoresToPrint;i++) 
        {
            int score = m_Scores[i];
            file << score;
            if (i < scoresToPrint - 1) {
                file << ";";
            }
        }
        file.close();
    }


}

void GameManager::EndGame(bool playerWin,int playerScore)
{
    GameEngine::Instance()->GetAudioManager()->PlaySound("Apple hit");
   
    if (playerWin) {
        GameManager::Instance()->AddScore(200);
        m_currentScore = playerScore;
    }
    
    GameManager::Instance()->gameOver = true;
    GameManager::Instance()->win = playerWin;
    UpdateScores();
}

void GameManager::UpdateScores()
{
    GameManager::WriteScores("scores.txt");
    GameManager::ReadScores("scores.txt");

}
