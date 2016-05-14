#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include "ImportantHeaders.h"
#include "VisibleGameObject.h"
#include "Game.h"

class Score: public VisibleGameObject
{
private:
    unsigned int m_nApplesAte, m_nLevel, m_nTime;
    const int CONST_APPLES_PER_LEVEL, CONST_TEXT_SIZE, CONST_TIME_START_VALUE;
    sf::Font m_Font;
    std::string m_strApplesAte = "APPLES: ", m_strLevel = "LEVEL: ", m_strDifficulty = "DIFFICULTY: ";
    enum Side
    {
        RIGHT,
        CENTER,
        LEFT
    };

public:

    Score();
    ~Score();

    void Update(float fElapsedTime);
    void AddScore();
    void ClearScore();
    void DrawTopPanel(sf::RenderWindow& rw);
    void SetUpText(sf::Text& text, std::string str, Side eSide);
    int GetApplesAte();

    void IncrementLevel();
    int  GetLevel();

    void DecrementTime();
    void AddTime(int nTime);
    void SubtractTime(int nTime);
    void ResetTime();
    void SetTime(int nTime);
    int  GetTime();
};

std::string ConcatenateString(const std::string& str, int n);
std::string ConcatenateString(const std::string& str_1, const std::string& str_2);

#endif // SCORE_H_INCLUDED
