#include "Apple.h"

Apple::Apple(sf::Color color)
{
    //make the apple a red square same size as the snake head
    m_rsApple.setSize(sf::Vector2f(11.0, 11.0));
    m_rsApple.setFillColor(color);
    //origin is set at top left corner of the square
    m_rsApple.setOrigin(m_rsApple.getLocalBounds().left - 1.0, m_rsApple.getLocalBounds().top - 1.0);

    AppleTeleport();
    SetColBox();
}

Apple::~Apple(){}


void Apple::Update(float fElapsedTime)
{
    SetColBox();
    DrawApple(Game::GetGameWindow());
}

void Apple::SetNextPosition()
{
    int nX = 0, nY = 0, nPossibleValues = 0, nTotalValues = 0, nEdgeLength = 0;

    const int CONST_POSITION_EXTENSION        = 24,//see Game CONST_TOP_BAR_L variable
              CONST_FIELD_SQUARE_LENGTH       = 12;


    nTotalValues = (Game::GetFieldWidth() - CONST_FIELD_SQUARE_LENGTH)/CONST_FIELD_SQUARE_LENGTH;

    int nSeed = 3, nRandNum = std::rand()%nSeed + 1;

    if(nRandNum == 1)
        nEdgeLength = 0;
    else
        nEdgeLength = 10;

    nPossibleValues = nTotalValues - nEdgeLength;

    if(nEdgeLength > 0)
    {
        int nRandNum = std::rand()%4 + 1;

        switch(nRandNum)
        {
        case 1:
            nX = (std::rand() % nPossibleValues);
            nY = (std::rand() % nPossibleValues);
            break;

        case 2:
            nX = nTotalValues - (std::rand() % nPossibleValues);
            nY = nTotalValues - (std::rand() % nPossibleValues);
            break;

        case 3:
            nX = nTotalValues - (std::rand() % nPossibleValues);
            nY = (std::rand() % nPossibleValues);
            break;

        case 4:
            nX = (std::rand() % nPossibleValues);
            nY = nTotalValues - (std::rand() % nPossibleValues);
            break;

        default:
            break;
        }
    }
    else
    {
        nX = (std::rand() % nPossibleValues);
        nY = (std::rand() % nPossibleValues);
    }

/*
    nX = (std::rand() % nPossibleValues) * CONST_FIELD_SQUARE_LENGTH
                 + CONST_FIELD_SQUARE_LENGTH;

    nY = (std::rand() % nPossibleValues) * CONST_FIELD_SQUARE_LENGTH
                  + CONST_FIELD_SQUARE_LENGTH  + CONST_POSITION_EXTENSION;
*/

    m_v2fNextPosition.x = nX * CONST_FIELD_SQUARE_LENGTH;
    m_v2fNextPosition.y = nY * CONST_FIELD_SQUARE_LENGTH + CONST_POSITION_EXTENSION;

    if(m_v2fNextPosition.x <= CONST_FIELD_SQUARE_LENGTH)
    {
        m_v2fNextPosition.x = CONST_FIELD_SQUARE_LENGTH;
    }
    else if(m_v2fNextPosition.x >= Game::GetFieldWidth() - 2 * CONST_FIELD_SQUARE_LENGTH)
    {
        m_v2fNextPosition.x = Game::GetFieldWidth() - 2 * CONST_FIELD_SQUARE_LENGTH;
    }

    if(m_v2fNextPosition.y <= (Game::GetGameWindow().getSize().y - Game::GetFieldWidth()) + CONST_FIELD_SQUARE_LENGTH)
    {
        m_v2fNextPosition.y = (Game::GetGameWindow().getSize().y - Game::GetFieldWidth()) + CONST_FIELD_SQUARE_LENGTH;
    }
    else if(m_v2fNextPosition.y >= Game::GetFieldWidth() - 2 * CONST_FIELD_SQUARE_LENGTH)
    {
        m_v2fNextPosition.y = Game::GetFieldWidth() - 2 * CONST_FIELD_SQUARE_LENGTH;
    }


}

void Apple::AppleTeleport()
{
    SetNextPosition();
    GetApple().setPosition(m_v2fNextPosition);
}

void Apple::SetColor(const sf::Color& color)
{
    GetApple().setFillColor(color);
}

sf::Color Apple::GetColor() const
{
    return m_rsApple.getFillColor();
}

void Apple::SetColBox()
{
    GetColBox().left   = GetApple().getPosition().x;
    GetColBox().width  = GetApple().getPosition().x + GetApple().getLocalBounds().width;
    GetColBox().top    = GetApple().getPosition().y;
    GetColBox().height = GetApple().getPosition().y + GetApple().getLocalBounds().height;
}


void Apple::DrawApple(sf::RenderWindow& rwMainWindow)
{
    rwMainWindow.draw(GetApple());
}

sf::RectangleShape& Apple::GetApple()
{
    return m_rsApple;
}

sf::Rect<float>& Apple::GetColBox()
{
    return m_rectColBox;
}
