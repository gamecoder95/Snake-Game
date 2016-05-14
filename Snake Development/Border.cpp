#include "Border.h"

Border::Border()
{
    CreateBorder();
}

Border::~Border(){}

void Border::Update(float fElapsedTime)
{
    DrawBorder(Game::GetGameWindow());
}

void Border::DrawBorder(sf::RenderWindow& rwMainWindow)
{
    for(int i = 0; i < GetBorder().size(); i++)
        rwMainWindow.draw(m_vectBorder[i]);
}

void Border::CreateBorder()
{
    const int CONST_SQUARE_SIDE = 12,
              CONST_NUM_SQUARES = Game::GetFieldWidth()/CONST_SQUARE_SIDE,
              CONST_POSITION_EXTENSION = 24;// see Game CONST_TOP_BAR_L variable

    for(int i = 0; i < (CONST_NUM_SQUARES - 1); i++)
    {
        //top
        sf::RectangleShape borderSquare(sf::Vector2f(11.0, 11.0));
        borderSquare.setFillColor(sf::Color(102, 0, 0));//this is the brown color
        borderSquare.setOrigin(borderSquare.getLocalBounds().left - 1.0, borderSquare.getLocalBounds().top - 1.0);
        borderSquare.setPosition(i * 12, CONST_POSITION_EXTENSION);
        GetBorder().push_back(borderSquare);

        //right side
        sf::RectangleShape borderSquare_2(sf::Vector2f(11.0, 11.0));
        borderSquare_2.setFillColor(sf::Color(102, 0, 0));//this is the brown color
        borderSquare_2.setOrigin(borderSquare_2.getLocalBounds().left - 1.0, borderSquare_2.getLocalBounds().top - 1.0);
        borderSquare_2.setPosition((CONST_NUM_SQUARES - 1) * CONST_SQUARE_SIDE, i * CONST_SQUARE_SIDE + CONST_POSITION_EXTENSION);
        GetBorder().push_back(borderSquare_2);

        //bottom
        sf::RectangleShape borderSquare_3(sf::Vector2f(11.0, 11.0));
        borderSquare_3.setFillColor(sf::Color(102, 0, 0));//this is the brown color
        borderSquare_3.setOrigin(borderSquare_3.getLocalBounds().left - 1.0, borderSquare_3.getLocalBounds().top - 1.0);
        borderSquare_3.setPosition( (i + 1) * CONST_SQUARE_SIDE, (CONST_NUM_SQUARES - 1) * CONST_SQUARE_SIDE + CONST_POSITION_EXTENSION);
        GetBorder().push_back(borderSquare_3);

        //left side
        sf::RectangleShape borderSquare_4(sf::Vector2f(11.0, 11.0));
        borderSquare_4.setFillColor(sf::Color(102, 0, 0));//this is the brown color
        borderSquare_4.setOrigin(borderSquare_4.getLocalBounds().left - 1.0, borderSquare_4.getLocalBounds().top - 1.0);
        borderSquare_4.setPosition(0.0, (i + 1) * CONST_SQUARE_SIDE + CONST_POSITION_EXTENSION);
        GetBorder().push_back(borderSquare_4);

    }


}

std::vector<sf::RectangleShape>& Border::GetBorder()
{
    return m_vectBorder;
}
