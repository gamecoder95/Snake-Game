#ifndef APPLE_H_INCLUDED
#define APPLE_H_INCLUDED

#include "ImportantHeaders.h"
#include "VisibleGameObject.h"
#include "Game.h"

class Apple: public VisibleGameObject
{
private:
    sf::Rect<float> m_rectColBox;
    sf::Vector2f m_v2fNextPosition;
    sf::RectangleShape m_rsApple;

    void SetNextPosition();
    void SetColBox();
    void DrawApple(sf::RenderWindow& rwMainWindow);

public:
    Apple(sf::Color color);
    ~Apple();

    void Update(float fElapsedTime);
    void AppleTeleport();

    void SetColor(const sf::Color& color);
    sf::Color GetColor() const;

    sf::RectangleShape& GetApple();
    sf::Rect<float>& GetColBox();
};




#endif // APPLE_H_INCLUDED
