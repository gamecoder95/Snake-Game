#ifndef BORDER_H_INCLUDED
#define BORDER_H_INCLUDED

#include "VisibleGameObject.h"
#include "ImportantHeaders.h"
#include "Game.h"

class Border: public VisibleGameObject
{
private:
    std::vector<sf::RectangleShape> m_vectBorder;

public:

    Border();
    ~Border();

    void Update(float fElapsedTime);
    void DrawBorder(sf::RenderWindow& rwMainWindow);
    void CreateBorder();
    std::vector<sf::RectangleShape>& GetBorder();

};

#endif // BORDER_H_INCLUDED
