#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "ImportantHeaders.h"
#include "VisibleGameObject.h"


class Wall: public VisibleGameObject
{
private:
    int m_nNumWallSquares;
    const int CONST_WALL_SQUARE_LENGTH, CONST_GAP_BETWEEN_SQUARES, CONST_MAX_NUM_SQUARES, CONST_MIN_NUM_SQUARES;
    float m_fPosition_X, m_fPosition_Y;
    std::vector<sf::RectangleShape> m_vectWall;
    char m_chOrientation;

public:
    Wall(float fPosition_X = 0.0, float fPosition_Y = 0.0, int nNumSquares = 2, char chOrientation = 'h');
    ~Wall();

    void Update(float fElapsedTime);
    void DrawWall(sf::RenderWindow& rw);
    void AddWallSquare();

    std::vector<sf::RectangleShape>& GetWall();

};

#endif // WALL_H_INCLUDED
