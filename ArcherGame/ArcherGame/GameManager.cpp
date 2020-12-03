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

void GameManager::ReadScores(std::string textFile) {
    fstream file;
    file.open(textFile, ios::in);
    if (!file) {
        std::cout << "Could not open file " << textFile;
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
        m_Scores = scores;
    }
}
