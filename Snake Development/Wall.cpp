#include "Wall.h"
#include "Game.h"

Wall::Wall(float fPosition_X, float fPosition_Y, int nNumSquares, char chOrientation)
           : m_fPosition_X(fPosition_X),
             m_fPosition_Y(fPosition_Y),
             m_nNumWallSquares(nNumSquares),
             m_chOrientation(chOrientation),
             CONST_WALL_SQUARE_LENGTH(11),
             CONST_GAP_BETWEEN_SQUARES(1),
             CONST_MAX_NUM_SQUARES(4),
             CONST_MIN_NUM_SQUARES(2)
{
    int nMinDistance = (CONST_WALL_SQUARE_LENGTH + CONST_GAP_BETWEEN_SQUARES);

    if(m_fPosition_X < nMinDistance)
        m_fPosition_X = nMinDistance;
    else if(m_fPosition_X > Game::GetFieldWidth())
        m_fPosition_X = Game::GetFieldWidth() - nMinDistance;

    if(m_fPosition_Y < (Game::GetGameWindow().getSize().y - Game::GetFieldWidth()) + nMinDistance)
        m_fPosition_Y = (Game::GetGameWindow().getSize().y - Game::GetFieldWidth()) + nMinDistance;
    else if(m_fPosition_Y > Game::GetFieldWidth())
        m_fPosition_Y = Game::GetFieldWidth() - nMinDistance;

    if(m_nNumWallSquares >= CONST_MAX_NUM_SQUARES)
        m_nNumWallSquares = CONST_MAX_NUM_SQUARES;

    if(m_nNumWallSquares <= CONST_MIN_NUM_SQUARES)
        m_nNumWallSquares = CONST_MIN_NUM_SQUARES;

    if(chOrientation != 'V' && chOrientation != 'v' && chOrientation != 'H' && chOrientation != 'h')
        chOrientation = 'h';//'h' or 'H' for horizontal, 'v' or 'V' for veritcal

    for(int i = 0; i < m_nNumWallSquares; i++)
        AddWallSquare();
}

Wall::~Wall()
{
    std::vector<sf::RectangleShape>::iterator it = m_vectWall.begin();
    while(it != m_vectWall.end())
        m_vectWall.erase(it);
}

void Wall::Update(float fElapsedTime)
{
    DrawWall(Game::GetGameWindow());
}

void Wall::DrawWall(sf::RenderWindow& rw)
{
    for(int i = 0; i < m_nNumWallSquares; i++)
        rw.draw(m_vectWall[i]);
}

void Wall::AddWallSquare()
{
    sf::RectangleShape wallSquare(sf::Vector2f(CONST_WALL_SQUARE_LENGTH, CONST_WALL_SQUARE_LENGTH));
    wallSquare.setFillColor(sf::Color::Cyan /*sf::Color(102, 0, 0)*/);//light brown
    wallSquare.setOrigin(-CONST_GAP_BETWEEN_SQUARES, -CONST_GAP_BETWEEN_SQUARES);

    float fDistanceToRight  = Game::GetFieldWidth() - m_fPosition_X,
          fDistanceToLeft   = m_fPosition_X,
          fDistanceToTop    = m_fPosition_Y - (Game::GetGameWindow().getSize().y - Game::GetFieldWidth()),
          fDistanceToBottom = Game::GetFieldWidth() - m_fPosition_Y,
          fSquareDistance   = CONST_WALL_SQUARE_LENGTH + CONST_GAP_BETWEEN_SQUARES;

    int   nSquareNumber = m_vectWall.size();

    if(nSquareNumber == 0)
        wallSquare.setPosition(m_fPosition_X, m_fPosition_Y);
    else
    {
        if(m_chOrientation == 'H' || m_chOrientation == 'h')
        {
            if(fDistanceToRight <= fDistanceToLeft)
            {
                float fStartPoint = m_fPosition_X;

                wallSquare.setPosition(fStartPoint - fSquareDistance * (nSquareNumber - 1), m_fPosition_Y);
            }
            else if(fDistanceToRight > fDistanceToLeft)
            {
                float fStartPoint = m_fPosition_X + fSquareDistance;

                wallSquare.setPosition(fStartPoint + fSquareDistance * (nSquareNumber - 1), m_fPosition_Y);
            }
        }
        else if(m_chOrientation == 'V' || m_chOrientation == 'v')
        {
            if(fDistanceToTop <= fDistanceToBottom)
            {
                float fStartPoint = m_fPosition_Y + fSquareDistance;

                wallSquare.setPosition(m_fPosition_X, fStartPoint + fSquareDistance * (nSquareNumber-1));
            }
            else if(fDistanceToTop > fDistanceToBottom)
            {
                float fStartPoint = m_fPosition_Y;

                wallSquare.setPosition(m_fPosition_X, fStartPoint - fSquareDistance * nSquareNumber);
            }
        }
    }

    m_vectWall.push_back(wallSquare);
}

std::vector<sf::RectangleShape>& Wall::GetWall()
{
    return m_vectWall;
}
