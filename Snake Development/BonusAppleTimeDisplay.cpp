#include "BonusAppleTimeDisplay.h"
#include "Game.h"

BonusAppleTimeDisplay::BonusAppleTimeDisplay()
                        :BonusAppleTimeDisplay(sf::Color::Red)
{
}

BonusAppleTimeDisplay::BonusAppleTimeDisplay(const sf::Color& color)
                        :m_fTimer(0.0),
                         m_fTimerLimit(0.0)
{

    Load("images/SnakeBonusAppleTime.png");
    assert(IsLoaded());
    SetOrigin(0, 0);

    m_rsApple.setSize(sf::Vector2f(CONST_APPLE_SIDE, CONST_APPLE_SIDE));
    m_rsApple.setOrigin(0, 0);
    m_rsApple.setFillColor(color);

    m_rsLoadingBar.setSize(sf::Vector2f(CONST_BAR_L, CONST_BAR_W));
    m_rsLoadingBar.setOrigin(0, 0);
    m_rsLoadingBar.setFillColor(color);

    SetPosition(146, 1);
}

BonusAppleTimeDisplay::~BonusAppleTimeDisplay(){}

void BonusAppleTimeDisplay::Update(float fElapsedTime)
{
    if(IsFinished())
        return;

    m_fTimer += fElapsedTime;

    m_rsLoadingBar.setScale((m_fTimerLimit - m_fTimer)/m_fTimerLimit, 1.0);

    Draw(Game::GetGameWindow());
}

void BonusAppleTimeDisplay::Draw(sf::RenderWindow& rw)
{
    rw.draw(GetSprite());
    rw.draw(m_rsApple);
    rw.draw(m_rsLoadingBar);
}

void BonusAppleTimeDisplay::SetPosition(float x, float y)
{
    VisibleGameObject::SetPosition(x, y);
    m_rsApple.setPosition(x + 4, y + 5);
    m_rsLoadingBar.setPosition(x + 19, y + 5);
}

void BonusAppleTimeDisplay::SetPosition(sf::Vector2f v2fPosition)
{
    SetPosition(v2fPosition.x, v2fPosition.y);
}

void BonusAppleTimeDisplay::SetTimerLimit(float fTimerLimit)
{
    m_fTimerLimit = fTimerLimit;
    m_fTimer = 0.0;
}

void BonusAppleTimeDisplay::SetColor(const sf::Color& color)
{
    m_rsApple.setFillColor(color);
    m_rsLoadingBar.setFillColor(color);
}

float BonusAppleTimeDisplay::GetTimerLimit()
{
    return m_fTimerLimit;
}

bool BonusAppleTimeDisplay::IsFinished()
{
    if(m_fTimer >= m_fTimerLimit)
    {
       m_fTimer == 0.0;
       return true;
    }
    return false;
}
