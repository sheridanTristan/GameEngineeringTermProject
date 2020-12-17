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
    GameEngine::Instance()->GetAudioManager()->LoadSound("Audio/birdflapping.wav", AudioScope::GLOBAL, "Flapping");
    ReadScores("scores.txt");
}
void GameManager::StepTurn() {
    if (player->GetTurn()) {
        player->SetTurn(false);
        enemy->OnTurnStart();
        enemy->SetTurn(true);
        m_currentScore = m_currentScore - 10;
    }
    else {
        enemy->SetTurn(false);
        player->OnTurnStart();
        player->SetTurn(true);
    }

}

void GameManager::SetupLevel(Player* player, Enemy* enemy, Bird* bird) {
    this->player = player;
    this->enemy = enemy;
    this->bird = bird;
    m_currentScore = 200;
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

void GameManager::BirdKill() {
    m_currentScore = m_currentScore + 60;
    GameEngine::Instance()->GetAudioManager()->PlaySound("Apple hit");
    GameEngine::Instance()->GetAudioManager()->StopSound(FLAPPING_CHANNEL);
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

void GameManager::EndGame(bool playerWin)
{
    GameEngine::Instance()->GetAudioManager()->PlaySound("Apple hit");
   
    if (playerWin) {
        GameManager::Instance()->AddScore(m_currentScore);
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
