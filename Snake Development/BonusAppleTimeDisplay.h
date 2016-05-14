#ifndef BONUSAPPLETIMEDISPLAY_H_INCLUDED
#define BONUSAPPLETIMEDISPLAY_H_INCLUDED

#include "ImportantHeaders.h"
#include "VisibleGameObject.h"

class BonusAppleTimeDisplay: public VisibleGameObject
{
private:
    sf::RectangleShape m_rsApple;
    sf::RectangleShape m_rsLoadingBar;
    float m_fTimerLimit, m_fTimer;
    const float CONST_APPLE_SIDE = 11.0, CONST_BAR_W = 11.0, CONST_BAR_L = 90.0;

public:

    BonusAppleTimeDisplay();
    BonusAppleTimeDisplay(const sf::Color& color);
    ~BonusAppleTimeDisplay();

    void  Update(float fElapsedTime);
    void  Draw(sf::RenderWindow& rw);
    void  SetPosition(float x, float y);
    void  SetPosition(sf::Vector2f v2fPosition);
    void  SetTimerLimit(float fTimerLimit);
    void  SetColor(const sf::Color& color);
    float GetTimerLimit();
    bool  IsFinished();

};

#endif // BONUSAPPLETIMEDISPLAY_H_INCLUDED
